#pragma once
#include <chrono>

namespace Cava 
{

	
	class SplashScreen
	{
	public:
		using Clock		= std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
		using Duration	= std::chrono::duration<double, std::milli>;
		
		struct Options
		{
			uint32_t width			= 876;
			uint32_t height			= 630;
			double minDuration		= 2000; // show atleast 4 seconds
			std::string imageFile;
		};

		SplashScreen(const Options& options);
		void show();
		void close();

		
	
	private:
		Options			options;
		TimePoint		startTime;
		uint32_t		gdwWindowXPos;
		uint32_t		gdwWindowYPos;
		uint32_t		gdwWindowWidth;
		uint32_t		gdwWindowHeight;
		
		HWND			splashWnd = nullptr;
		WNDCLASSEX		wc;
	};

}