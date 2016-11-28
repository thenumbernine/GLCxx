#pragma once

#include "Shader/GLHandle.h"
#include <vector>
#include <string>

namespace Shader {

struct Shader : public GLHandle {
	typedef GLHandle Super;

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
};

typedef ShaderType<GL_VERTEX_SHADER_ARB> VertexShader;
typedef ShaderType<GL_FRAGMENT_SHADER_ARB> FragmentShader;

};

