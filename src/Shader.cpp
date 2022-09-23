#include "Shader/Shader.h"
#include "Common/Macros.h"
#include "Common/Exception.h"
#include <string>
#include <sstream>

namespace Shader {

Shader::Shader() {}

Shader::Shader(Shader const & shader) {
	this->operator=(shader);
}

Shader & Shader::operator=(Shader const & shader) {
	contents = shader.contents;
	return *this;
}

Shader::Shader(int shaderType)
: Super(glCreateShader(shaderType))
{
}

Shader & Shader::setSources(std::vector<std::string> const & sources) {
	std::vector<GLchar const *> cstrs(sources.size());
	std::vector<GLint> lens(sources.size());
	for (int i = 0; i < (int)sources.size(); ++i) {
		cstrs[i] = sources[i].c_str();
		lens[i] = sources[i].length();
	}
	glShaderSource((*this)(), cstrs.size(), cstrs.data(), lens.data());
	return *this;
}

Shader & Shader::compile() {
	glCompileShader((*this)());
	GLint compiled = 0;
	glGetShaderiv((*this)(), GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		throw Common::Exception() << "failed to compile shader.\n" << getLog();
	}
	return *this;
}

std::string Shader::nameForType(int shaderType) {
	switch (shaderType) {
	case GL_VERTEX_SHADER: return "Vertex";
	case GL_FRAGMENT_SHADER: return "Fragment";
	}
	return "Unknown";
}

};

