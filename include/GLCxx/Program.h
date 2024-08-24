#pragma once

#include "GLCxx/Shader.h"
#include <list>
#include <vector>

namespace GLCxx {

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
	Program(
		std::string const & vertexShaderCode,
		std::string const & fragmentShaderCode
	);
	Program(
		std::string && vertexShaderCode,
		std::string && fragmentShaderCode
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

	// uniform templates...
	// TODO Tensor implementations of these:

	template<typename T>
	Program & setUniform(std::string const & name, T value1) {
		if constexpr (std::is_integral_v<T>) {
			glUniform1i(getUniformLocation(name), value1);
		} else if constexpr (std::is_floating_point_v<T>) {
			glUniform1f(getUniformLocation(name), value1);
		} else {
			throw Common::Exception() << "this should be a static_assert failure but C++ meh";
		}
		return *this;
	}

	template<typename T>
	Program & setUniform(std::string const & name, T value1, T value2) {
		if constexpr (std::is_integral_v<T>) {
			glUniform2i(getUniformLocation(name), value1, value2);
		} else if constexpr (std::is_floating_point_v<T>) {
			glUniform2f(getUniformLocation(name), value1, value2);
		} else {
			throw Common::Exception() << "this should be a static_assert failure but C++ meh";
		}
		return *this;
	}

	template<typename T>
	Program & setUniform(std::string const & name, T value1, T value2, T value3) {
		if constexpr (std::is_integral_v<T>) {
			glUniform3i(getUniformLocation(name), value1, value2, value3);
		} else if constexpr (std::is_floating_point_v<T>) {
			glUniform3f(getUniformLocation(name), value1, value2, value3);
		} else {
			throw Common::Exception() << "this should be a static_assert failure but C++ meh";
		}
		return *this;
	}

	template<typename T>
	Program & setUniform(std::string const & name, T value1, T value2, T value3, T value4) {
		if constexpr (std::is_integral_v<T>) {
			glUniform4i(getUniformLocation(name), value1, value2, value3, value4);
		} else if constexpr (std::is_floating_point_v<T>) {
			glUniform4f(getUniformLocation(name), value1, value2, value3, value4);
		} else {
			throw Common::Exception() << "this should be a static_assert failure but C++ meh";
		}
		return *this;
	}


	// If you don't mind runtime then a TODO could be to lookup the uniform type and call glUniformMatrix if it's a matrix, or glUniform otherwise
	// This is pretty much what the Lua framework does.

	template<int dim, typename T>
	Program & setUniformMatrix(std::string const & name, T const * const value, bool transpose = false, int count = 1) {
		if constexpr (dim == 2) {
			// I guess uniform matrix is only for float and double ...
			if constexpr (std::is_same_v<T, float>) {
				glUniformMatrix2fv(getUniformLocation(name), count, transpose, value);
			} else if constexpr (std::is_same_v<T, double>) {
				glUniformMatrix2dv(getUniformLocation(name), count, transpose, value);
			} else {
				throw Common::Exception() << "this should be a static_assert failure but C++ meh";
			}
		} else if constexpr (dim == 3) {
			// I guess uniform matrix is only for float and double ...
			if constexpr (std::is_same_v<T, float>) {
				glUniformMatrix3fv(getUniformLocation(name), count, transpose, value);
			} else if constexpr (std::is_same_v<T, double>) {
				glUniformMatrix3dv(getUniformLocation(name), count, transpose, value);
			} else {
				throw Common::Exception() << "this should be a static_assert failure but C++ meh";
			}
		} else if constexpr (dim == 4) {
			if constexpr (std::is_same_v<T, float>) {
				glUniformMatrix4fv(getUniformLocation(name), count, transpose, value);
			} else if constexpr (std::is_same_v<T, double>) {
				glUniformMatrix4dv(getUniformLocation(name), count, transpose, value);
			} else {
				throw Common::Exception() << "this should be a static_assert failure but C++ meh";
			}
		}
		return *this;
	}

	static std::string getVersionPragma();
};

}
