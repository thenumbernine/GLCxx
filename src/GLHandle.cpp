#include "Shader/GLHandle.h"
#include <vector>

namespace Shader {

GLHandle::GLHandle()
{}

GLHandle::GLHandle(HandleType handleContents) 
: contents(std::make_shared<Contents>(handleContents))
{}

GLHandle::GLHandle(const GLHandle& handle) {
	this->operator=(handle);
}

GLHandle& GLHandle::operator=(const GLHandle& handle) {
	contents = handle.contents;
	return *this;
}

GLHandle::~GLHandle() {
}

GLHandle::HandleType GLHandle::operator()() const { 
	if (!contents.get()) return HandleType();
	return contents->handle;
}

std::string GLHandle::getLog(HandleType handle) {

	GLint length = 0;
	glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB,& length);
	if (length <= 0) return std::string();

	std::vector<GLcharARB> log(length);
	GLsizei written  = 0;
	glGetInfoLogARB(handle, length, &written, &log[0]);

	return std::string(log.begin(), log.end());
}

};
