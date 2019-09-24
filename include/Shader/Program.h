#pragma once

#include "Shader/Shader.h"
#include <list>

namespace Shader {

struct ProgramWrapperInfo {
	static void getivFn(GLuint a, GLenum b, GLint* c) {
		glGetProgramiv(a,b,c);
	}

	static void getInfoLogFn(GLuint a, GLint b, GLint* c, GLchar* d) {
		glGetProgramInfoLog(a,b,c,d);
	}

	static void deleteFn(GLuint a) {
		glDeleteProgram(a);
	}
};

struct Program : public Wrapper<ProgramWrapperInfo> {
	using Super = Wrapper;

protected:
	//all attached shaders 
	std::list<Shader> attached;
public:
	
	Program();
	Program(const Program& program);
	Program& operator=(const Program& program);

	Program(std::vector<Shader>& shaders);
	
	Program& attach(const Shader& shader);
	Program& link();

	template<int shaderType>
	Program& attachShader(std::vector<std::string>& sources) {
		ShaderType<shaderType> shader;
		shader.setSources(sources);
		attach(shader);
		return *this;
	}

	Program& use();
	Program& done();	//useNone for this.  had to think of a clever new name.
	static void useNone();

	int getUniformLocation(const std::string& name);

	template<typename T> Program& setUniform(const std::string& name, T value);
	template<typename T> Program& setUniform(const std::string& name, T value1, T value2);
	template<typename T> Program& setUniform(const std::string& name, T value1, T value2, T value3);
};

}
