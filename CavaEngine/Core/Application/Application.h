#pragma once
#include "Renderer.h"
#include "Core/Window/Window.h"
#include "Core/Event/InputEvents.h"
#include "Core/GUI/Gui.h"
#include "Core/Window/SplashScreen.h"


namespace Cava
{

	
	class Gui;
	class SplashScreen;

	///<summary>
	///	Create main application inheriting Renderer class and in application Application::run(pRenderer, options);
	///</summary>
	class Application : public Window::ICallbacks
	{
	public:
		friend class Renderer;
		struct Options
		{
			std::string title = "Cava Engine";
			std::string icon = "";

			Window::Options windowOptions = Window::Options();
			SplashScreen::Options splashOptions = SplashScreen::Options();
			Gui::Options guiOptions = Gui::Options();

			bool showSplashScreen = true;
			bool createConsole = true;
		};

		static void run(Renderer* renderer, const Options& opts);

		void init();
		void quit();

		Options		getOptions() { return options; }
		Window* getWindow() { return window; }
		Renderer* getRenderer() { return renderer; }

	protected:

		Application(Renderer* renderer);
		~Application() = default;

		void runInternal(const Options& opts);

		void handleKeyboard(const KeyboardEvent& evt) override;
		void handleMouse() override;
		void handleRenderFrame() override;
		void handleResize(uint32_t width, uint32_t height) override;

		Options			options;
		Window*			window			= nullptr;
		Renderer*		renderer		= nullptr;
		SplashScreen*	splashScreen	= nullptr;
		Gui*			gui				= nullptr;

	private:
		void loadInternalAssets();

		Application()
		{
			options = Options();
			window = Window::create(options.windowOptions, this);
		}
	};
	

}
