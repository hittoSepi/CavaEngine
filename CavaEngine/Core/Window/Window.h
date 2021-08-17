#pragma once

#include <string>
#include "Core/Window/BaseWindow.h"

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

namespace Cava {


	class Window : public BaseWindow
	{
	public:
		friend class WindowCallbacks;

		static Window* create(const Options& opts, ICallbacks* callbacks);

		void init(bool showWindow) override;	// create and open window here
		void quit() override;	// destroy window here

		void messageLoop() override;
		void pollEvents() override;

		void show() override;
		void hide() override;

		void BeginFrame() override;
		void EndFrame() override;
		
		Rectangle<int> getClientSize() override;

		void setClearColor(float r, float g, float b, float a) override;
		void setMode(Mode windowMode) override;
		void setIcon(std::string filename) override;
		void setTitle(std::string title) override;
		void setPosition(uint32_t x, uint32_t y) override;

		void resize(uint32_t width, uint32_t height) override;

		GLFWwindow* getGLFWwindow() { return window; }
		void close(); // signals to close app.

		bool isRunning(); // returns glfwShouldWindowClose();

	protected:

		Window(const Options& options, ICallbacks* callbacks) :
			BaseWindow(options, callbacks),
			options(options), callbacks(callbacks)

		{
			LogInfo(options.title);
		}
		
		Options				options;
		ICallbacks*			callbacks	= nullptr;
		GLFWwindow*			window		= nullptr;
		GLFWmonitor*		monitor		= nullptr;
		const GLFWvidmode*	videoMode	= nullptr;
	private:
		Window()
		{
			options = Options();
			init(true);
		}

	};


}