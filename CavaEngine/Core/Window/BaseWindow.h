#pragma once
#include <Windows.h>
#include "Core/Event/InputEvents.h"
#include "Core/Math/Rectangle.h"

namespace Cava {

	class BaseWindow
	{
	public:
		using WindowHandle = HWND;
		
		enum class Mode
		{
			Fullscreen,
			BordelessFullscreen,
			Borderless,
			Windowed,
			Hidden
		};

		enum class WindowState
		{
			Normal,
			Minimized,
			Maximized,
		};

		struct ICallbacks
		{
			virtual void handleRenderFrame() = 0;
			virtual void handleKeyboard(const Cava::KeyboardEvent& evt) = 0;
			virtual void handleMouse() = 0;
			virtual void handleResize(uint32_t width, uint32_t height) = 0;

			ICallbacks() {}

		};

		struct Options
		{
			std::string title	= "Cava Engine";
			Mode mode			= Mode::Windowed;
			WindowState state	= WindowState::Normal;
			bool vsync			= false;
			bool resizeable		= false;
			uint32_t width		= 1280;
			uint32_t height		= 720;
			
		};


		virtual ~BaseWindow() {}

		virtual void init(bool showWindow) = 0; /// Initialize and open window
		virtual void quit() = 0; /// Prepare to die.

		virtual void show() = 0;
		virtual void hide() = 0;
		
		virtual void messageLoop() = 0;
		virtual void pollEvents() = 0;

		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
		
		
		virtual Rectangle<int> getClientSize() = 0;
		virtual void setMode(Mode windowMode) = 0;

		virtual void setClearColor(float r, float g, float b, float a) = 0;
		virtual void setTitle(std::string title) = 0;
		virtual void setPosition(uint32_t x, uint32_t y) = 0;
		virtual void resize(uint32_t width, uint32_t height) = 0;

		virtual void setIcon(std::string filename) {}

		const std::string& getWindowTitle() { return options.title; }
		const WindowHandle& getWindowHandle() { return windowHandle; }
		Options				getOptions() { return options; }

	protected:
		BaseWindow(const Options& opts, ICallbacks* callbacks) :
			options(opts), callbacks(callbacks)
		{}

		BaseWindow() {}

		Options			options			= Options();
		ICallbacks*		callbacks		= nullptr;
		WindowHandle	windowHandle	= nullptr;
	private:
	};

}
