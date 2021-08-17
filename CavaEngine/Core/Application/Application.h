#pragma once
#include "Renderer.h"
#include "Core/Window/Window.h"
#include "Core/Event/InputEvents.h"
#include "Core/Window/SplashScreen.h"


namespace Cava {

class SplashScreen;
	
///<summary>
///	Create main application inheriting Renderer class and in application Application::run(pRenderer, options);
///</summary>
class Application: public Window::ICallbacks
{
public:
	friend class Renderer;
	struct Options
	{
		std::string title					= "Cava Engine";
		std::string icon					= "";
		Window::Options windowOptions		= Window::Options();
		SplashScreen::Options splashOptions = SplashScreen::Options();
		bool showSplashScreen				= true;
		bool createConsole					= false;
	};
	
	static void run(Renderer *renderer, const Options& opts);
	
	void init();
	void quit();

	static void setInstance(HINSTANCE instance_)
	{
		LogInfo("");
		instance = instance_;
	}
	
protected:
		
	Application(Renderer *renderer);
	~Application() = default;
	
	void runInternal(const Options& opts);
	
	void handleKeyboard(const KeyboardEvent& evt) override;
	void handleMouse() override;
	void handleRenderFrame() override;
	void handleResize(uint32_t width, uint32_t height) override;
	
	Options			options;
	Window			*window			= nullptr;
	Renderer		*renderer		= nullptr;
	SplashScreen	*splashScreen	= nullptr;
	inline static HINSTANCE instance = nullptr;
private:
	void loadInternalAssets();
	
	Application()
	{
		options = Options();
		window = Window::create(options.windowOptions, this);
	}
};

}
