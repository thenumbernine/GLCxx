#include "Shader/Shader.h"
#include "Common/Macros.h"
#include <string>
#include <sstream>

namespace Shader {

Shader::Shader() {}

Shader::Shader(const Shader &shader) {
	this->operator=(shader);
}

Shader &Shader::operator=(const Shader &shader) {
	contents = shader.contents;
	return *this;
}

Shader::Shader(int shaderType)
: Super(glCreateShaderObjectARB(shaderType))
{
}

Shader &Shader::setSources(const std::vector<std::string> &sources) {
	std::vector<const GLcharARB*> szsources(sources.size());
	std::vector<GLint> lengths(sources.size());
	for (int i = 0; i < sources.size(); ++i) {
		szsources[i] = sources[i].c_str();
		lengths[i] = sources[i].length();
	}
	glShaderSourceARB((*this)(), szsources.size(), &szsources[0], &lengths[0]);
	return *this;
}

Shader &Shader::compile() {
	glCompileShaderARB((*this)());
	return *this;
}

std::string Shader::nameForType(int shaderType) {
	switch (shaderType) {
	case GL_VERTEX_SHADER_ARB: return "Vertex";
	case GL_FRAGMENT_SHADER_ARB: return "Fragment";
	}
	return "Unknown";
}

};

