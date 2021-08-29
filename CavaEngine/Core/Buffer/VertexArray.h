#pragma once
#include <vector>

namespace Cava
{
	
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray(){}

		void draw();
		
		void bind();
		void unbind();
		
		void destroy();


		
		void setAttrib(uint32_t arraySlot, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
		void enableAttaribArray(uint32_t index);
		

		uint32_t getID() { return vertexArray; }
		
		void setData(const std::vector<glm::vec2>& v, uint32_t drawmode = GL_STATIC_DRAW);
		void setData(const std::vector<glm::vec3>& v, uint32_t drawmode = GL_STATIC_DRAW);
		void setData(const std::vector<glm::vec4>& v, uint32_t drawmode = GL_STATIC_DRAW);
		void setData(const glm::mat4& m);
		void setData(const glm::mat3& m);
		void setData(std::vector<float> v, uint32_t drawmode = GL_STATIC_DRAW);
		void setData(int val);
		void setData(bool val);
		void setData(GLuint val);
	protected:
		uint32_t vertexArray;
	};


	
}
