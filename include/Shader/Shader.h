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

	int shaderType = {};

	Shader();
	Shader & operator=(Shader const & shader);
	Shader & operator=(Shader && shader);
	Shader(Shader const & shader);
	Shader(Shader && shader);
	
	//create an uncompiled, uninitialized shader handle
	Shader(int shaderType_);

	//create a shader of the specified type with the specified sources and compile it
	Shader(int shaderType_, std::vector<std::string> const & sources);
	Shader(int shaderType_, std::string const & source);

	//add a source to the shader
	Shader & setSources(std::vector<std::string> const & sources);
	
	//compile the shader
	Shader & compile();

	//return the name for which type of shader
	static std::string nameForType(int shaderType);
};

template<typename ...Params> Shader VertexShader(Params&&... params) { return Shader(GL_VERTEX_SHADER, std::forward<Params>(params)...); }
template<typename ...Params> Shader FragmentShader(Params&&... params) { return Shader(GL_FRAGMENT_SHADER, std::forward<Params>(params)...); }

#if defined(GL_GEOMETRY_SHADER)
template<typename ...Params> Shader GeometryShader(Params&&... params) { return Shader(GL_GEOMETRY_SHADER, std::forward<Params>(params)...); }
#endif
#if defined(GL_TESS_CONTROL_SHADER)
template<typename ...Params> Shader TessControlShader(Params&&... params) { return Shader(GL_TESS_CONTROL_SHADER, std::forward<Params>(params)...); }
#endif
#if defined(GL_TESS_EVALUATION_SHADER)
template<typename ...Params> Shader TessEvalShader(Params&&... params) { return Shader(GL_TESS_EVALUATION_SHADER, std::forward<Params>(params)...); }
#endif
#if defined(GL_COMPUTE_SHADER) 
template<typename ...Params> Shader ComputeShader(Params&&... params) { return Shader(GL_COMPUTE_SHADER, std::forward<Params>(params)...); }
#endif
}
