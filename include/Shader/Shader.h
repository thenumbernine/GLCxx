#pragma once

#include "Shader/Wrapper.h"
#include <vector>
#include <string>

namespace Shader {

struct Shader : public Wrapper<
	glGetShaderiv,
	glGetShaderInfoLog,
	glDeleteShader
> {
	typedef Wrapper Super;

	Shader();
	Shader(const Shader& shader);
	Shader& operator=(const Shader& shader);
	
	//create an uncompiled, uninitialized shader handle
	Shader(int shaderType);

	//add a source to the shader
	virtual Shader& setSources(const std::vector<std::string>& sources);
	
	//compile the shader
	virtual Shader& compile();

	//return the name for which type of shader
	static std::string nameForType(int shaderType);
};

template<int shaderType>
struct ShaderType : public Shader {
	typedef Shader Super;
	
	ShaderType() {}

	ShaderType(const ShaderType& shader) {
		this->operator=(shader);
	}
	
	ShaderType& operator=(const ShaderType& shader) {
		contents = shader.contents;
		return *this;
	}

	//create a shader of the specified type with the specified sources and compile it
	ShaderType(const std::vector<std::string>& sources) 
	: Super(shaderType)
	{
		setSources(sources);
		compile();
	}

	ShaderType(const std::string& source)
	: Super(shaderType)
	{
		setSources(std::vector<std::string>{source});
		compile();
	}
};

typedef ShaderType<GL_VERTEX_SHADER> VertexShader;
typedef ShaderType<GL_FRAGMENT_SHADER> FragmentShader;

#if defined(GL_GEOMETRY_SHADER)
typedef ShaderType<GL_GEOMETRY_SHADER> GeometryShader;
#endif
#if defined(GL_TESS_CONTROL_SHADER)
typedef ShaderType<GL_TESS_CONTROL_SHADER> TessControlShader;
#endif
#if defined(GL_TESS_EVALUATION_SHADER)
typedef ShaderType<GL_TESS_EVALUATION_SHADER> TessEvalShader;
#endif
#if defined(GL_COMPUTE_SHADER) 
typedef ShaderType<GL_COMPUTE_SHADER> ComputeShader;
#endif
};
