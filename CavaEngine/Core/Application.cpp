#include "Core/Cava.h"
#include "Application.h"

namespace Cava {
	
	void Application::run(Renderer* renderer, const Options& opts)
	{
		try {
			if (opts.createConsole)
				CreateConsole();
			
			LogInfo("");
			
			Application app = Application(renderer);
			app.runInternal(opts);
		}
		catch(...)
		{
			LogError("Exception thrown.");
		}
		
	}

	
	Application::Application(Renderer *renderer):
		renderer(renderer)
	{
		LogInfo("");
		if(renderer == nullptr)
		{
			LogError("Renderer is null.");
		}
	}

	
	void Application::runInternal(const Options& opts)
	{
		LogInfo("");
		options = opts;

		init();
	
		window->messageLoop();

		quit();
	}

	
	void Application::init()
	{
		LogInfo("");
	

		window = Window::create(options.windowOptions, this);
		window->init();
		
		loadInternalAssets();
		
		renderer->init();
	}


	void Application::quit()
	{
		LogInfo("");
		renderer->quit();
		
		delete window;
		glfwTerminate();
	}


	void Application::loadInternalAssets()
	{
		LogInfo("");
	}

	
	void Application::handleKeyboard(const KeyboardEvent& evt)
	{
	}

	void Application::handleMouse()
	{
		
	}

	void Application::handleRenderFrame()
	{
		renderer->update();
		renderer->render();
	}

	void Application::handleResize(uint32_t width, uint32_t height)
	{
		renderer->resize(width, height);
	}


}