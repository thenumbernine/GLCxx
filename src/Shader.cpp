#include "Shader/Shader.h"
#include "Common/Macros.h"
#include "Common/File.h"
#include <string>
#include <sstream>

namespace Shader {

Shader::Shader(int shaderType)
: Super()
{
	handle = glCreateShaderObjectARB(shaderType);
}

void Shader::setSource(std::string source) {
	const char *sources[] = {source.c_str()};
	glShaderSourceARB(handle, numberof(sources), sources, NULL);
}

void Shader::compile() {
	glCompileShaderARB(handle);
}

void Shader::createFromSource(std::string filename, std::string prefix) {
	std::ostringstream s;
	if (!prefix.empty()) s << prefix;
	if (!filename.empty()) s << Common::File::read(filename);
	setSource(s.str());
	compile();
}


std::string Shader::nameForType(int shaderType) {
	switch (shaderType) {
	case GL_VERTEX_SHADER_ARB: return "Vertex";
	case GL_FRAGMENT_SHADER_ARB: return "Fragment";
	}
	return "Unknown";
}

};

