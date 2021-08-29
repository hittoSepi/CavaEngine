#include "Core/Cava.h"
#include "VertexArray.h"

#include <vector>

#include "Core/Cava.h"
#include "Core/Cava.h"
#include "Core/Cava.h"
#include "Core/Cava.h"

namespace Cava
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &vertexArray);
	}

	
	void VertexArray::draw()
	{
		bind();
		

		unbind();
		
	}

	void VertexArray::bind()
	{
		 glBindVertexArray(vertexArray);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
		
	}

	void VertexArray::destroy()
	{
		glDeleteVertexArrays(1, &vertexArray);
	}

	
	void VertexArray::setAttrib(uint32_t arraySlot, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		enableAttaribArray(arraySlot);
	}

	void VertexArray::enableAttaribArray(uint32_t index)
	{
		glEnableVertexAttribArray(index);
	}

	
	void VertexArray::setData(const std::vector<glm::vec2>& v, uint32_t drawmode)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec2), v.data(), drawmode);

		
	}

	
	void VertexArray::setData(const std::vector<glm::vec3>& v, uint32_t drawmode)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec2), v.data(), drawmode);
	}

	
	void VertexArray::setData(const std::vector<glm::vec4>& v, uint32_t drawmode)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec2), v.data(), drawmode);
	}

	void VertexArray::setData(const glm::mat4& m)
	{
	}

	
	void VertexArray::setData(const glm::mat3& m)
	{
	}

	
	void VertexArray::setData(std::vector<float> v, uint32_t drawmode)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec2), v.data(), drawmode);
	}

	
	void VertexArray::setData(int val)
	{
	}

	
	void VertexArray::setData(bool val)
	{
	}

	
	void VertexArray::setData(GLuint val)
	{
	}
}
