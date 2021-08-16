#pragma once

#include <string>
#include "Core/Window/BaseWindow.h"

struct GLFWwindow;

namespace Cava {


	class Window : public BaseWindow
	{
	public:
		friend class WindowCallbacks;

		static Window* create(const Options& opts, ICallbacks* callbacks);

		void init() override;	// create and open window here
		void quit() override;	// destroy window here

		void messageLoop() override;
		void pollEvents() override;
		
		Rectangle<int> getClientSize() override;

		void setMode(Mode windowMode) override;
		
		void setTitle(std::string title) override;
		void resize(uint32_t width, uint32_t height) override;
		void setPosition(uint32_t x, uint32_t y) override;

		void close(); // signals to close app.

		bool isRunning(); // returns glfwShouldWindowClose();

	protected:

		Window(const Options& options, ICallbacks* callbacks) :
			BaseWindow(options, callbacks),
			options(options), callbacks(callbacks)

		{
			LogInfo(options.title);
		}
		
		Options			options;
		ICallbacks*		callbacks	= nullptr;
		GLFWwindow*		window		= nullptr;
	private:
		Window()
		{
			options = Options();
			init();
		}

	};


}