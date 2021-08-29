#pragma once
#include <cstdint>
#include <imgui/imgui.h>

namespace Cava
{


	class Application;
	class Window;
	
	class Gui
	{
	public:

		enum class WindowType: uint32_t
		{
			NoTitle			= ImGuiWindowFlags_NoTitleBar,
			NoCollapse		= ImGuiWindowFlags_NoCollapse,
			NoMove			= ImGuiWindowFlags_NoMove,
			NoResize		= ImGuiWindowFlags_NoResize,
			
			StaticNoTitle	= NoTitle | NoCollapse | NoMove | NoResize,
			Static			= NoCollapse | NoMove | NoResize
		};
		
		struct Options
		{
			bool showPerformanceCounters = true;
		};
		
		Gui(Application *app);

		void begin();
		void render();
		void quit();
	
	protected:
		void showPerformanceCounters();
		
		Application *app;
		Options options;
	};


}