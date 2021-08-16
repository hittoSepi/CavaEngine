#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define GLFW_INCLUDE_NONE

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

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// OpenGL Headers
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


using int2	 = glm::ivec2;
using int3	 = glm::ivec3;
using float2 = glm::vec2;
using float3 = glm::vec3;


#pragma comment(lib, "glfw3dll.lib")


// Core Engine Headers
#include "Core/Application/Application.h"
#include "Core/Application/Renderer.h"

#include "Core/Debug/Debug.h"
#include "Core/Event/InputEvents.h"
#include "Core/Window/Window.h"

#include "Core/Math/Rectangle.h"
