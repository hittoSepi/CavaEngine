#include "Core/Cava.h"
#include "FileUtils.h"


namespace Cava {
std::string GetWorkDirectory()
{
	TCHAR buffer[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, buffer);
	//size_t pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer);
}
}