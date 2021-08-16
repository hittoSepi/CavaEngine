#pragma once
namespace Cava {
class Renderer
{
public:
	Renderer() = default;
	virtual ~Renderer() {};
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void quit() = 0;
	virtual void resize(uint32_t width, uint32_t height) = 0;
protected:
	
};
}