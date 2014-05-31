#pragma once

#include "Shader/GLHandle.h"
#include <string>

namespace Shader {

class Shader : public GLHandle {
	typedef GLHandle Super;
public:

	Shader(int shaderType);

	void setSource(std::string source);
	void compile();

	void createFromSource(
		std::string filename, 
		std::string prefix = std::string());

	static std::string nameForType(int shaderType);
};

template<int shaderType>
class ShaderType : public Shader {
	typedef Shader Super;
public:
	ShaderType()
	: Super(shaderType)
	{}
	
	void createFromSource(std::string filename, std::string prefix = std::string()) {
		Super::createFromSource(filename, shaderType, prefix);
	}
};

typedef ShaderType<GL_VERTEX_SHADER_ARB> VertexShader;
typedef ShaderType<GL_FRAGMENT_SHADER_ARB> FragmentShader;

};

