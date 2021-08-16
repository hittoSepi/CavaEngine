#pragma once
#include "Core/Cava.h"
using namespace Cava;

class Game: public Renderer
{
public:
	Game();
	~Game() override;
	
	void init() override;
	void update() override;
	void render() override;
	void quit() override;
	void resize(uint32_t width, uint32_t height) override;
	
	void loadAssets();
};