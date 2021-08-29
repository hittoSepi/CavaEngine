#pragma once
#include <deque>
#include <future>
#include "Core/Debug/Debug.h"


namespace Cava
{

class JobSystem {
public:
	using Ptr = std::unique_ptr<JobSystem>;
	
	static Ptr create(size_t threads)
	{
		return Ptr(new JobSystem(threads));
	}

	
	// finish enques a "stop the thread" message for every thread, then waits for them:
	void finish() {
		{
			LogVerbose("Waiting threads to finish...");
			std::unique_lock<std::mutex> l(m);
			for (auto&& unused : finished) {
				work.push_back({});
			}
		}
		v.notify_all();
		finished.clear();
		LogInfo("Threads finished.")
	}

	
	// queue( lambda ) will enqueue the lambda into the tasks for the threads
	// to use.  A future of the type the lambda returns is given to let you get
	// the result out.
	template<class F, class R = std::result_of_t<F& ()>>
	std::future<R> queue(F&& f) {
		// wrap the function object into a packaged task, splitting
		// execution from the return value:
		std::packaged_task<R()> p(std::forward<F>(f));

		auto r = p.get_future(); // get the return value before we hand off the task
		{
			std::unique_lock<std::mutex> l(m);
			work.emplace_back(std::move(p)); // store the task<R()> as a task<void()>
		}
		v.notify_one(); // wake a thread to work on the task

		return r; // return the future result of the task
	}

	
	// abort() cancels all non-started tasks, and tells every working thread
	// stop running, and waits for them to finish up.
	void abort() {
		cancel_pending();
		finish();
	}
	
	// cancel_pending() merely cancels all non-started tasks:
	void cancel_pending() {
		std::unique_lock<std::mutex> l(m);
		work.clear();
	}
	
private:
	
	JobSystem(size_t threadCount)
	{
		start(threadCount);
	}

	
	// the mutex, condition variable and deque form a single
	// thread-safe triggered queue of tasks:
	std::mutex m;
	std::condition_variable v;
	// note that a packaged_task<void> can store a packaged_task<R>:
	std::deque<std::packaged_task<void()>> work;

	// this holds futures representing the worker threads being done:
	std::vector<std::future<void>> finished;



	// start N threads in the thread pool.
	void start(std::size_t N = 1) {
		LogInfo(std::string("Created " + std::to_string(N) +" threads."));
		for (std::size_t i = 0; i < N; ++i)
		{
			// each thread is a std::async running this->thread_task():
			finished.push_back(
				std::async(
					std::launch::async,
					[this] { thread_task(); }
				)
			);
		}
	}

	
	// the work that a worker thread does:
	void thread_task() {
		while (true) {
			// pop a task off the queue:
			std::packaged_task<void()> f;
			{
				// usual thread-safe queue code:
				std::unique_lock<std::mutex> l(m);
				if (work.empty()) {
					v.wait(l, [&] {return !work.empty(); });
				}
				f = std::move(work.front());
				work.pop_front();
			}
			// if the task is invalid, it means we are asked to abort:
			if (!f.valid()) return;
			// otherwise, run the task:
			f();
		}
	}
};

}