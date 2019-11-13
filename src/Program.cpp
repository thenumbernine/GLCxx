#include "Shader/Program.h"
#include "Common/Exception.h"

namespace Shader {

Program::Program() {}

Program::Program(const Program& program) {
	this->operator=(program);
}

Program& Program::operator=(const Program& program) {
	contents = program.contents;
	attached = program.attached;
	return *this;
}

Program::Program(std::vector<Shader>& shaders) {
	contents = std::make_shared<Contents>(glCreateProgram());
	for (Shader& shader : shaders) {
		attach(shader);
	}
	link();
}

Program::Program(std::vector<Shader>&& shaders) {
	contents = std::make_shared<Contents>(glCreateProgram());
	for (Shader& shader : shaders) {
		attach(shader);
	}
	link();
}

Program& Program::attach(const Shader& shader) {
	glAttachShader((*this)(), shader());
	attached.push_back(shader);
	return *this;
}

Program& Program::link() {
	int status = -1;
	glGetProgramiv((*this)(), GL_LINK_STATUS, &status);

	//don't link twice!!! intel drivers are crashing when you do that
	if (status != 0) throw Common::Exception() << "won't link, program " << (*this)() << " already has link status " << status;

	glLinkProgram((*this)());
	
	GLint linked = 0;
	glGetProgramiv((*this)(), GL_LINK_STATUS, (int*)&linked);
	if (!linked) {
		throw Common::Exception() << "failed to link program.\n" << getLog();
	}
	for (Shader& shader : attached) {
		glDetachShader((*this)(), shader());
	}
	return *this;
}

Program& Program::use() {
	glUseProgram((*this)());
	return *this;
}

Program& Program::done() {
	Program::useNone();
	return *this;
}

void Program::useNone() {
	glUseProgram(0);
}

int Program::getUniformLocation(const std::string& name) {
	return glGetUniformLocation((*this)(), name.c_str());
}

template<>
Program& Program::setUniform<int>(const std::string& name, int value) {
	use();
	glUniform1i(getUniformLocation(name), value);
	return *this;
}

template<>
Program& Program::setUniform<bool>(const std::string& name, bool value) {
	use();
	glUniform1i(getUniformLocation(name), value);
	return *this;
}

template<>
Program& Program::setUniform<float>(const std::string& name, float value) {
	use();
	glUniform1f(getUniformLocation(name), value);
	return *this;
}

template<>
Program& Program::setUniform<float>(const std::string& name, float value1, float value2) {
	use();
	glUniform2f(getUniformLocation(name), value1, value2);
	return *this;
}

template<>
Program& Program::setUniform<float>(const std::string& name, float value1, float value2, float value3) {
	use();
	glUniform3f(getUniformLocation(name), value1, value2, value3);
	return *this;
}

};
