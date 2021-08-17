#pragma once

#include <imgui/imgui.h>

namespace Cava {
	class Application;
	class Window;
	
	class Gui
	{
	public:
		Gui(Application *app);

		void begin();
		void render();
		void quit();
	protected:
		Application *app;

	};


}