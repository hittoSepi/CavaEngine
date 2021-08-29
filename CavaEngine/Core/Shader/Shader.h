#pragma once
#include <string>

namespace Cava
{


	class Shader
	{
	public:
		enum class Type : GLenum
		{
			VERTEX = GL_VERTEX_SHADER,
			GEOMETRY = GL_GEOMETRY_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
			COMPUTE = GL_COMPUTE_SHADER
		};

		struct ShaderPart
		{
			std::string filename;
			Type		type;
			std::string source;
			uint32_t	id;

			Type getType() { return type; }
		};



		Shader(std::string name);
		
		void addShaderFile(Type type, std::string filename);

		void load();
		void destroy();   // deletes program & shaders
		void bind();
		
		void detachShaders();
		
		GLint getUniformLocation(const char* name);

		bool isLinked() { return linked; }

		void bindAttribLocation( GLuint location, const char * name);
		void bindFragDataLocation( GLuint location,	const char * name );

		
		void setUniform(const char* name, float x, float y, float z);
		void setUniform(const char* name, const glm::vec2& v);
		void setUniform(const char* name, const glm::vec3& v);
		void setUniform(const char* name, const glm::vec4& v);
		void setUniform(const char* name, const glm::mat4& m);
		void setUniform(const char* name, const glm::mat3& m);
		void setUniform(const char* name, float val);
		void setUniform(const char* name, int val);
		void setUniform(const char* name, bool val);
		void setUniform(const char* name, GLuint val);

		uint32_t	getProgram() { return program; }
		std::string getName() { return name; }

	protected:
		std::string						name;
		uint32_t						program;
		std::map<Type, ShaderPart>		shaders;
		std::map<const char*, int>		uniformLocations;
		bool							linked;
	
	private:
		void compile();
		void link();
		void getUniformLocations();
		void debugPrintUniformNames();
	};
	
}