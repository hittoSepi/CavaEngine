#include "Core/Cava.h"
#include "Shader.h"

#include "Core/Debug/Debug.h"
#include "Core/OS/FileUtils.h"

namespace Cava
{


	Shader::Shader(std::string name) :
		name(name), linked(false)
	{
		LogInfo(name);
	}


	void Shader::bind()
	{
		glUseProgram(program);
	}

	void Shader::detachShaders()
	{
		for(auto shader : shaders)
		{
			glDetachShader(program, shader.second.id);
		}
	}
	
	
	GLint Shader::getUniformLocation(const char* name)
	{
		auto it = uniformLocations.find(name);
		if (it != uniformLocations.end())
			return it->second;

		LogError("Uniform not found!");

	}

	
	void Shader::bindAttribLocation(GLuint location, const char* name)
	{
		glBindAttribLocation(program, location, name);
	}

	
	void Shader::bindFragDataLocation(GLuint location, const char* name)
	{
		glBindFragDataLocation(program, location, name);
	}


	void Shader::setUniform(const char* name, float x, float y, float z)
	{
		glUniform3f(getUniformLocation(name), x, y, z);
	}

	
	void Shader::setUniform(const char* name, const glm::vec2& v)
	{
		glUniform2f(getUniformLocation(name), v.x, v.y);
		
	}
	

	void Shader::setUniform(const char* name, const glm::vec3& v)
	{
		glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
	}

	
	void Shader::setUniform(const char* name, const glm::vec4& v)
	{
		glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
	}

	
	void Shader::setUniform(const char* name, const glm::mat4& m)
	{
		glUniformMatrix4fv(getUniformLocation(name),  1, GL_FALSE, &m[0][0]);
	}
	

	void Shader::setUniform(const char* name, const glm::mat3& m)
	{
		glUniformMatrix3fv(getUniformLocation(name),  1, GL_FALSE, &m[0][0]);
	}
	

	void Shader::setUniform(const char* name, float val)
	{
		glUniform1f(getUniformLocation(name), val);
	}
	

	void Shader::setUniform(const char* name, int val)
	{
		glUniform1i(getUniformLocation(name), val);
	}

	
	void Shader::setUniform(const char* name, bool val)
	{
		glUniform1i(getUniformLocation(name), val);
	}
	

	void Shader::setUniform(const char* name, GLuint val)
	{
		glUniform1i(getUniformLocation(name), val);
	}
	
	
	void Shader::addShaderFile(Type type, std::string filename)
	{
		if (linked) return;

		ShaderPart part = ShaderPart();
		part.type = type;
		part.filename = filename;
		shaders.emplace(type, part);
	}


	void Shader::load()
	{
		if (linked) return;

		for (auto shader : shaders)
		{
			auto filename = shader.second.filename;
			shaders.emplace(shader.first, readFile(shader.second.filename));
		}
		compile();
	}

	
	void Shader::destroy()
	{
		detachShaders();
		for(auto shader : shaders)
		{
			glDeleteShader(shader.second.id);
		}
		glDeleteProgram(program);
	}


	void Shader::compile()
	{
		int  success;
		char infoLog[512];

		// compile shader parts and bind those to shader program
		for (auto shader : shaders)
		{
			auto src = shader.second.source;
			auto id = shader.second.id;

			glCreateShader((uint32_t)id);

			glShaderSource(id, 1, (const GLchar* const*)src.c_str(), NULL);
			glCompileShader(id);

			glGetShaderiv(id, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(id, 512, NULL, infoLog);
				std::string msg = "Shader Compilation failed: " + std::string(infoLog);
				LogError(msg.c_str());
			}
			else
			{
				glAttachShader(program, id);
			}
		}
		
		link();
		getUniformLocations();
	}


	void Shader::link()
	{
		int		success;
		char	infoLog[512];

		// link shader
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (success == GL_FALSE)
		{
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			if (length > 0) {
				char* c_log = new char[length];
				int written = 0;
				glGetProgramInfoLog(program, length, &written, infoLog);

			}
			throw new std::exception(std::string("Shader " + name + " linking failed.\n" + infoLog).c_str());
		}
		linked = true;
	}


	void Shader::getUniformLocations()
	{
		uniformLocations.clear();
		GLint numUniforms = 0;

		glGetProgramInterfaceiv(program, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

		GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };

		for (GLint i = 0; i < numUniforms; ++i) {
			GLint results[4];
			glGetProgramResourceiv(program, GL_UNIFORM, i, 4, properties, 4, nullptr, results);

			if (results[3] != -1) continue;  // Skip uniforms in blocks
			const GLint nameBufSize = results[0] + 1;
			char* name = new char[nameBufSize];
			glGetProgramResourceName(program, GL_UNIFORM, i, nameBufSize, nullptr, name);
			uniformLocations[name] = results[2];
			delete[] name;
		}
	}

	void Shader::debugPrintUniformNames()
	{
		std::string names = name + " uniforms: \n";
		for(auto uniform: uniformLocations)
		{
			names += uniform.second + "\n";
		}
	}


}