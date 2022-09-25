#pragma once

#include "Shader/Wrapper.h"
#include <vector>
#include <string>

namespace Shader {

struct ShaderWrapperInfo {
	static constexpr char const * name = "Shader";
	
	static void getivFn(GLuint a, GLenum b, GLint* c) {
		glGetShaderiv(a,b,c);
	}

	static void getInfoLogFn(GLuint a, GLint b, GLint* c, GLchar* d) {
		glGetShaderInfoLog(a,b,c,d);
	}

	static void deleteFn(GLuint a) {
		glDeleteShader(a);
	}
};

struct Shader : public Wrapper<ShaderWrapperInfo> {
	using Super = Wrapper;

	Shader();
	Shader(Shader const & shader);
	Shader& operator=(Shader const & shader);
	
	//create an uncompiled, uninitialized shader handle
	Shader(int shaderType);

	//add a source to the shader
	virtual Shader& setSources(std::vector<std::string> const & sources);
	
	//compile the shader
	virtual Shader& compile();

	//return the name for which type of shader
	static std::string nameForType(int shaderType);
};

template<int shaderType>
struct ShaderType : public Shader {
	using Super = Shader;
	
	ShaderType() {}

	ShaderType(ShaderType const & shader) {
		this->operator=(shader);
	}
	
	ShaderType & operator=(ShaderType const & shader) {
		contents = shader.contents;
		return *this;
	}

	//create a shader of the specified type with the specified sources and compile it
	ShaderType(std::vector<std::string> const & sources) 
	: Super(shaderType)
	{
		setSources(sources);
		compile();
	}

	ShaderType(std::string const & source)
	: Super(shaderType)
	{
		setSources(std::vector<std::string>{source});
		compile();
	}
};

using VertexShader = ShaderType<GL_VERTEX_SHADER>;
using FragmentShader = ShaderType<GL_FRAGMENT_SHADER>;

#if defined(GL_GEOMETRY_SHADER)
using GeometryShader = ShaderType<GL_GEOMETRY_SHADER>;
#endif
#if defined(GL_TESS_CONTROL_SHADER)
using TessControlShader = ShaderType<GL_TESS_CONTROL_SHADER>;
#endif
#if defined(GL_TESS_EVALUATION_SHADER)
using TessEvalShader = ShaderType<GL_TESS_EVALUATION_SHADER>;
#endif
#if defined(GL_COMPUTE_SHADER) 
using ComputeShader = ShaderType<GL_COMPUTE_SHADER>;
#endif
}
