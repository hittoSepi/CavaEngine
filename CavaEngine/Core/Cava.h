#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

// C++ RunTime Header Files
#include <ctime>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iosfwd>
#include <memory>
#include <chrono>
#include <cstdint>
#include <thread>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>


// OpenGL Headers
#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>
#include <glad/glad.h>

using int2		= glm::ivec2;
using int3		= glm::ivec3;
using float2	= glm::vec2;
using float3	= glm::vec3;
using IntHash	= uint64_t;

#pragma comment(lib, "glfw3dll.lib")

/////////////////////////
// Core Headers

// Debugging
#include "Core/Debug/Debug.h"

// Application Framework
#include "Core/Application/Application.h"
#include "Core/Application/Renderer.h"

// OS Specific code
#include "Core/OS/FileUtils.h"

// Events
#include "Core/Event/InputEvents.h"

// GUI
#include "Core/GUI/Gui.h"

// Window 
#include "Core/Window/Window.h"
#include "Core/Window/SplashScreen.h"

// Shader
#include "Core/Shader/Shader.h"

// Buffers
#include "Core/Buffer/Vertex.h"
#include "Core/Buffer/VertexBuffer.h"
#include "Core/Buffer/VertexArray.h"

// Math
#include "Core/Math/Rectangle.h"

// Misc
#include "Core/Singleton/Singleton.h"
#include "Core/Thread/ThreadPool.h"

/////////////////////////
// Engine Headers

#include "Engine/BaseObject.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/Component.h"

#include "Engine/GameObject/GameObjectManager.h"
#include "Engine/Component/ComponentManager.h"

#include "Engine/Engine.h"