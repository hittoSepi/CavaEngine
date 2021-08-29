#include "Core/Cava.h"
#include "Core/Window/SplashScreen.h"
#include <locale>


namespace Cava
{

	LRESULT CALLBACK SplashProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	    return DefWindowProc(hWnd, message, wParam, lParam);
	}

	SplashScreen::SplashScreen(const Options& options) :
		options(options)
	{
		LogInfo("");

		
		DWORD dwFrameWidth = GetSystemMetrics(SM_CXSIZEFRAME);
		DWORD dwFrameHeight = GetSystemMetrics(SM_CYSIZEFRAME);
		DWORD dwMenuHeight = GetSystemMetrics(SM_CYMENU);
		gdwWindowXPos = (uint32_t)(GetSystemMetrics(SM_CXSCREEN) - options.width) / 2;
		gdwWindowYPos = (uint32_t)(GetSystemMetrics(SM_CYSCREEN) - options.height) / 2.25;
		gdwWindowWidth = options.width + dwFrameWidth * 2;
		gdwWindowHeight = options.height + dwFrameHeight * 2;
	}


	void SplashScreen::show()
	{
		LogInfo("");
		
		auto instance = GetModuleHandle(NULL);
		auto file =  GetWorkDirectory() + R"(\Data\UI\Images\Splash.bmp)";

		HBITMAP bitmap = (HBITMAP)LoadImage(instance, file.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetWindowsErrorString();
		
		wc = {0};
		wc.cbSize			= sizeof(WNDCLASSEX);
		wc.style			= CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc		= SplashProc;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
	    wc.hInstance		= instance;
	    wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground	= CreatePatternBrush(bitmap);
		wc.lpszMenuName		= NULL;
		wc.lpszClassName	= "CavaEngineSplash";

		if(!RegisterClassEx(&wc)) {
			GetWindowsErrorString();
		}

		splashWnd = CreateWindowEx(0L,
			"CavaEngineSplash",
			"CavaEngineSplash",
			WS_POPUP  | WS_VISIBLE, // and any other flags you need
			gdwWindowXPos, // these just center the
			gdwWindowYPos, // window on the screen
			gdwWindowWidth, // Calculated width
			gdwWindowHeight, // and height
			NULL, // Parent window
			NULL, // Menu (don't want one)
			instance, // hInstance
			NULL // Other Parameters
		);
				
		ShowWindow(splashWnd, 1);
		UpdateWindow(splashWnd);

		startTime			= Clock::now();
	}


	void SplashScreen::close()
	{

		TimePoint current = Clock::now();
		const Duration dur = current - startTime;

		double elapsed = dur.count();

		while (elapsed <= options.minDuration)
		{
			current = Clock::now();
			Duration dur = current - startTime;
			elapsed = dur.count();
			this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		CloseWindow(splashWnd);
		DestroyWindow(splashWnd);
	}


}



