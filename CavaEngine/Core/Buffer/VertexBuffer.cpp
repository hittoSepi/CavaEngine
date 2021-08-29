#include "Core/Cava.h"

namespace Cava
{


	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &vertexBuffer);
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	}

	void VertexBuffer::setVertices(const std::vector<Vertex>& vertices)
	{
		this->vertices = vertices;
	}

	void VertexBuffer::generate()
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(vertices[0].size()), vertices.data(), GL_STATIC_DRAW);
	}

	void VertexBuffer::destroy()
	{
		glDeleteBuffers(1, &vertexBuffer);
	}


}