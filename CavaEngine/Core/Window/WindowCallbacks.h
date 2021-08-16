#pragma once

#include <Windows.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include "Window.h"

namespace Cava
{
	class WindowCallbacks
	{
	public:
		
		static void error_callback(int code, const char* msg)
		{
			LogError(msg);
		}

		
		static void keyboardCallback(GLFWwindow* pGlfwWindow, int key, int scanCode, int action, int modifiers)
		{

			if(key == (int)KeyCode::ESCAPE)
			{
				glfwSetWindowShouldClose(pGlfwWindow, 1);
			}
			else {
				Window* pWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
				if (pWindow != nullptr)
				{
					pWindow->callbacks->handleKeyboard(KeyboardEvent(key, scanCode, action, modifiers));
				}
			}
			
		}
		

		static void mouseMoveCallback(GLFWwindow* pGlfwWindow, double mouseX, double mouseY)
		{

		}
		

		static void resizeCallback(GLFWwindow* pGlfwWindow, int width, int height)
		{
			Window* pWindow = (Window*)glfwGetWindowUserPointer(pGlfwWindow);
			if (pWindow != nullptr)
			{
				
				pWindow->callbacks->handleResize(width, height);
			}
		}

	};
}
