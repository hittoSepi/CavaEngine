#include <stdint.h>
#include "Core/Application/Renderer.h"

namespace Cava {

	void Renderer::initInternal()
	{
		init();
	}

	
	void Renderer::quitInternal()
	{
		quit();
	}

	
	void Renderer::updateInternal()
	{
		update();
	}


	void Renderer::renderInternal()
	{
		render();
	}




}