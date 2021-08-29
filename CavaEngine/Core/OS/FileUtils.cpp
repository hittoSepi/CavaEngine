#include "Core/Cava.h"
#include "FileUtils.h"


namespace Cava
{

	
	std::string GetWorkDirectory()
	{
		TCHAR buffer[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, buffer);
		return std::string(buffer);
	}


	std::string readFile(std::string filename)
	{
		std::ifstream in(filename.c_str());
		if(!in)
		{
			LogError(std::string("Could Not Open File: " + filename).c_str());
		}

		std::string line, res;
		while(std::getline(in, line))
		{
			res += line + "\n";
		}

		return res;
	}

	
}