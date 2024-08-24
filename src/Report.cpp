#include "GLCxx/Report.h"
#include <iostream>
#include <map>

namespace GLCxx {

#define MAKE_PAIR(x)	std::make_pair(x, #x)
static std::map<GLuint, std::string> errNames = {
	MAKE_PAIR(GL_INVALID_ENUM),
	MAKE_PAIR(GL_INVALID_VALUE),
	MAKE_PAIR(GL_INVALID_OPERATION),
	MAKE_PAIR(GL_INVALID_FRAMEBUFFER_OPERATION),
#if defined(GL_INVALID_INDEX)
	MAKE_PAIR(GL_INVALID_INDEX),
#endif
};
#undef MAKE_PAIR

void report(std::string const & filename, int line, std::string const & msg) {
	auto err = glGetError();
	if (!err) return;

	std::string s = filename + "(" + std::to_string(line) + "): ";
	if (msg != "") {
		s += msg + ": ";
	}
	s += std::to_string(err);
	auto i = errNames.find(err);
	if (i != errNames.end()) {
		s += " " + i->second;
	}
	
	std::cerr << s << std::endl;
}

}
