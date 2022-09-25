#pragma once

#include "Shader/Shader.h"
#include <list>
#include <vector>

namespace Shader {

struct ProgramWrapperInfo {
	static constexpr char const * name = "Program";

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
	Program(Program && program);
	Program & operator=(Program const & program);
	Program & operator=(Program && program);

	Program(std::vector<Shader>& shaders);
	Program(std::vector<Shader>&& shaders);
	
	// alright shorthand ...
	// should I provide a vector-of-vectors-of-strings to pass into VertexShader and FragmentShader?
	// or a 2-param list of vector-of-strings to pass to VertexShader and FragmentShader?
	// or maybe just 2-param strings?  no need to pass the Shader a vector-of-strings?
	Program(
		std::vector<std::string> const & vertexShaderCode,
		std::vector<std::string> const & fragmentShaderCode
	);
	Program(
		std::vector<std::string> && vertexShaderCode,
		std::vector<std::string> && fragmentShaderCode
	);

	void init(std::vector<Shader> const & shaders);
	void init(std::vector<Shader> && shaders);
	
	Program & attach(Shader const & shader);
	Program & link();

	Program & attachShader(int shaderType, std::vector<std::string> & sources);

	Program & use();
	Program const & use() const;
	Program & done();	//useNone for this.  had to think of a clever new name.
	Program const & done() const;
	static void useNone();

	int getUniformLocation(std::string const & name) const;
	int getAttribLocation(std::string const & name) const;

	template<typename T> Program & setUniform(std::string const & name, T value);
	template<typename T> Program & setUniform(std::string const & name, T value1, T value2);
	template<typename T> Program & setUniform(std::string const & name, T value1, T value2, T value3);
};

}
