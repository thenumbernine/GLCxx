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
	contents = std::make_shared<Contents>(glCreateProgramObjectARB());
	for (Shader& shader : shaders) {
		attach(shader);
	}
	link();
}

Program& Program::attach(const Shader& shader) {
	glAttachObjectARB((*this)(), shader());
	attached.push_back(shader);
	return *this;
}

Program& Program::link() {
	glLinkProgramARB((*this)());
	GLint linked = 0;
	glGetObjectParameterivARB((*this)(), GL_OBJECT_LINK_STATUS_ARB, &linked);
	if (!linked) {
		throw Common::Exception() << "failed to link program.\n"
			<< getAllLogs();
	}
	return *this;
}

std::string Program::getAllLogs() {
	std::string log;
	for (Shader& shader : attached) {
		log += getLog(shader());
	}
	log += getLog((*this)());
	return log;
}

Program& Program::use() {
	glUseProgramObjectARB((*this)());
	return *this;
}

Program& Program::done() {
	Program::useNone();
	return *this;
}

void Program::useNone() {
	glUseProgramObjectARB(0);
}

int Program::getUniformLocation(const std::string& name) {
	return glGetUniformLocationARB((*this)(), name.c_str());
}

template<>
Program& Program::setUniform<int>(const std::string& name, int value) {
	use();
	glUniform1iARB(getUniformLocation(name), value);
	return *this;
}

template<>
Program& Program::setUniform<float>(const std::string& name, float value) {
	use();
	glUniform1fARB(getUniformLocation(name), value);
	return *this;
}

template<>
Program& Program::setUniform<float>(const std::string& name, float value1, float value2) {
	use();
	glUniform2fARB(getUniformLocation(name), value1, value2);
	return *this;
}

template<>
Program& Program::setUniform<float>(const std::string& name, float value1, float value2, float value3) {
	use();
	glUniform3fARB(getUniformLocation(name), value1, value2, value3);
	return *this;
}


};

