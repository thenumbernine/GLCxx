#include "Shader/GLHandle.h"
#include <vector>

namespace Shader {

GLHandle::GLHandle() 
: handle(HandleType())
{}

GLHandle::~GLHandle() {
	if (handle) glDeleteObjectARB(handle);
}

std::string GLHandle::getLog(HandleType handle) {

	GLint length = 0;
	glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
	if (length <= 0) return std::string();

	std::vector<GLcharARB> log(length);
	GLsizei written  = 0;
	glGetInfoLogARB(handle, length, &written, &log[0]);

	return std::string(log.begin(), log.end());
}

};
