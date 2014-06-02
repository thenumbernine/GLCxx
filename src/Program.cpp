#include "Shader/Program.h"
#include "Common/Exception.h"

namespace Shader {

Program::Program() {
	handle = glCreateProgramObjectARB();
}

void Program::attach(HandleType extHandle) {
	glAttachObjectARB(handle, extHandle);
	attachedHandles.push_back(extHandle);
}

void Program::attach(const Shader &shader) {
	glAttachObjectARB(handle, shader.getHandle());
	attachedHandles.push_back(shader.getHandle());
}

void Program::link() {
	glLinkProgramARB(handle);
	GLint linked = 0;
	glGetObjectParameterivARB(handle, GL_OBJECT_LINK_STATUS_ARB, &linked);
	if (!linked) {
		throw Common::Exception() << "failed to link program.\n"
			<< getAllLogs();
	}
}

void Program::use() {
	glUseProgramObjectARB(handle);
}

void Program::useNone() {
	glUseProgramObjectARB(0);
}

void Program::attachShader(std::string filename, int shaderType, std::string prefix) {
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(shaderType);
	shader->createFromSource(filename, prefix);
	ownedShaders.push_back(shader);
	attach(shader->getHandle());
}

void Program::attachVertexShader(std::string filename, std::string prefix)	{
	attachShader(filename, GL_VERTEX_SHADER_ARB, prefix);
}

void Program::attachFragmentShader(std::string filename, std::string prefix) {
	attachShader(filename, GL_FRAGMENT_SHADER_ARB, prefix);
}

std::string Program::getAllLogs() {
	std::string log;
	for (HandleType handle : attachedHandles) {
		log += getLog(handle);
	}
	log += getLog(handle);
	return log;
}

int Program::getUniformLocation(std::string name) {
	return glGetUniformLocationARB(handle, name.c_str());
}


template<>
void Program::setUniform<int>(std::string name, int value) {
	use();
	glUniform1iARB(getUniformLocation(name), value);
}

template<>
void Program::setUniform<float>(std::string name, float value) {
	use();
	glUniform1fARB(getUniformLocation(name), value);
}

template<>
void Program::setUniform<float>(std::string name, float value1, float value2) {
	use();
	glUniform2fARB(getUniformLocation(name), value1, value2);
}

};

