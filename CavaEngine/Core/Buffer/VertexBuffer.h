#pragma once
#include <vector>

namespace Cava
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer(){}

		void bind();
		void unbind();

		size_t size() { return vertices.size(); }
		
		void setVertices(const std::vector<Vertex>& vertices);
		void generate();
		void destroy();
		
		uint32_t getID() { return vertexBuffer; }
	protected:
		uint32_t vertexBuffer;
		std::vector<Vertex> vertices;
	};
	
}
