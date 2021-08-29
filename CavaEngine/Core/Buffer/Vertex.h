#pragma once

namespace Cava
{
	struct Vertex
	{
		virtual size_t size() const =0;
	};
	
	struct Vertex2: Vertex
	{
		size_t size() const override { return sizeof(Vertex2); }
		glm::vec2 position;
	};

	struct Vertex2UV: Vertex
	{
		size_t size() const override { return sizeof(Vertex2UV); }
		glm::vec2 position;
		glm::vec2 uv;
	};
	
	struct Vertex2Color: Vertex
	{
		size_t size() const override { return sizeof(Vertex2Color); }
		glm::vec2 position;
		glm::vec4 color;
	};
		
	struct Vertex2ColorUV: Vertex
	{
		size_t size() const override { return sizeof(Vertex2ColorUV); }
		glm::vec2 position;
		glm::vec4 color;
		glm::vec2 uv;
	};

	struct Vertex3: Vertex
	{
		size_t size() const override { return sizeof(Vertex3); }
		glm::vec3 position;
	};
	
	struct Vertex3UV: Vertex
	{
		size_t size() const override { return sizeof(Vertex3UV); }
		glm::vec3 position;
		glm::vec2 uv;
	};

	struct Vertex3Color: Vertex
	{
		size_t size() const override { return sizeof(Vertex3Color); }
		glm::vec3 position;
		glm::vec4 color;
	};
	
	struct Vertex3ColorUV: Vertex
	{
		size_t size() const override { return sizeof(Vertex3ColorUV); }
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 uv;
	};
	
}
