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
	Program(Program const & program);
	Program & operator=(Program const & program);

	Program(std::vector<Shader>& shaders);
	Program(std::vector<Shader>&& shaders);
	void init(std::vector<Shader> & shaders);
	
	Program & attach(Shader const & shader);
	Program & link();

	template<int shaderType>
	Program & attachShader(std::vector<std::string>& sources) {
		ShaderType<shaderType> shader;
		shader.setSources(sources);
		attach(shader);
		return *this;
	}

	Program & use();
	Program & done();	//useNone for this.  had to think of a clever new name.
	static void useNone();

	int getUniformLocation(std::string const & name);
	int getAttribLocation(std::string const & name);

	template<typename T> Program & setUniform(std::string const & name, T value);
	template<typename T> Program & setUniform(std::string const & name, T value1, T value2);
	template<typename T> Program & setUniform(std::string const & name, T value1, T value2, T value3);
};

}
