#include "Core/Cava.h"
#include "Core/Debug/Debug.h"
#include "Core/Math/Rectangle.h"
#include "Core/Window/Window.h"
#include "Core/Window/WindowCallbacks.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3native.h>
#include <stb_image.h>

namespace Cava
{

	Window* Window::create(const Options& opts, ICallbacks* callbacks)
	{
		LogInfo("");
		glfwSetErrorCallback(WindowCallbacks::error_callback);
		if (!glfwInit())
		{
			LogError("Could not initialize GLFW.");
		}

		Window* window = new Window(opts, callbacks);
		if (window == nullptr)
		{
			LogError("Could not create Window.");
		}
		return window;

	}


	void Window::init(bool createWindow)
	{
		// set window creation options
		glfwWindowHint(GLFW_RESIZABLE, options.resizeable);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

		switch (options.mode)
		{
		case Mode::Borderless:
			glfwWindowHint(GLFW_DECORATED, false);
			break;

		case Mode::BordelessFullscreen:
			glfwWindowHint(GLFW_MAXIMIZED, true);
			glfwWindowHint(GLFW_DECORATED, false);
			glfwWindowHint(GLFW_FLOATING, true);

			monitor = glfwGetPrimaryMonitor();
			videoMode = glfwGetVideoMode(monitor);

			options.width = videoMode->width;
			options.height = videoMode->height;

			break;

		case Mode::Hidden:
			glfwWindowHint(GLFW_VISIBLE, false);
			break;

		case Mode::Fullscreen:
			glfwWindowHint(GLFW_DECORATED, false);
			glfwWindowHint(GLFW_MAXIMIZED, true);
			break;

		case Mode::Windowed:
			break;

		default:break;
		}

		if (!createWindow) {
			glfwWindowHint(GLFW_VISIBLE, false);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only

		window = glfwCreateWindow(options.width, options.height, options.title.c_str(), monitor, nullptr);
		glfwMakeContextCurrent(window);

		if (!window)
		{
			LogError("Error creating GLFWwindow.");
		}

		windowHandle = glfwGetWin32Window(window);

		glfwSetWindowPos(window, (GetSystemMetrics(SM_CXSCREEN) - options.width) / 2, (GetSystemMetrics(SM_CYSCREEN) - options.height) / 2);

		// create glfw window
		glfwSetWindowUserPointer(window, this);

		// set callbacks
		glfwSetKeyCallback(window, WindowCallbacks::keyboardCallback);
		glfwSetWindowSizeCallback(window, WindowCallbacks::resizeCallback);
	/*
		glfwSetMouseButtonCallback(window,	Callbacks::mouseButtonCallback);
		glfwSetCursorPosCallback(window,	Callbacks::mouseMoveCallback);
		glfwSetScrollCallback(window,		Callbacks::mouseWheelCallback);
		glfwSetCharCallback(window,			Callbacks::charInputCallback);
		glfwSetDropCallback(window,			Callbacks::droppedFileCallback);
	*/

		if (!gladLoadGL()) {
			LogError("Failed to initialize OpenGL context");
		}

		
		setClearColor(0.05f, 0.05f, 0.07f, 1.0f);
		glfwSwapInterval(options.vsync == true ? 1 : 0);

		LogInfo("\n\nCreated OpenGL Context:\nOpenGL " << glGetString(GL_VERSION) << "\n" << glGetString(GL_RENDERER) << "\n");

	}


	void Window::quit()
	{
		LogInfo("");
		glfwTerminate();
	}


	void Window::pollEvents()
	{
		glfwPollEvents();
	}


	void Window::messageLoop()
	{
		LogInfo("");
		while (isRunning())
		{
			pollEvents();
			
			callbacks->handleRenderFrame();

			
		}
	}


	bool Window::isRunning()
	{
		return !glfwWindowShouldClose(window);
	}


	void Window::close()
	{
		LogInfo("");
		glfwSetWindowShouldClose(window, 1);
	}


	void Window::hide()
	{
		glfwHideWindow(window);
	}


	void Window::show()
	{
		glfwShowWindow(window);
	}


	void Window::BeginFrame()
	{
		glViewport(0, 0, options.width, options.height);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	
	void Window::EndFrame()
	{
		glfwSwapBuffers(window);
	}


	void Window::setClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	
	
	void Window::setMode(Mode windowMode)
	{

	}


	Rectangle<int> Window::getClientSize()
	{
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		return Rectangle<int>(0, 0, w, h);
	}


	void Window::setIcon(std::string filename)
	{
		GLFWimage icon[1];
		icon[0].pixels = stbi_load(filename.c_str(), &icon[0].width, &icon[0].height, nullptr, 4);
		glfwSetWindowIcon(window, 1, icon);
		stbi_image_free(icon[0].pixels);
	}


	void Window::setTitle(std::string title)
	{
		LogInfo(title);
		options.title = title;
		glfwSetWindowTitle(window, title.c_str());
	}


	void Window::resize(uint32_t width, uint32_t height)
	{
		LogInfo(width << ", " << height);
		options.width = width;
		options.height = height;
		glfwSetWindowSize(window, width, height);
		callbacks->handleResize(width, height);
	}


	void Window::setPosition(uint32_t x, uint32_t y)
	{
		LogInfo(x << ", " << y);
		glfwSetWindowPos(window, x, y);
	}



}