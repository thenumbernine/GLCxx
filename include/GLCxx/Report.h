#pragma once

#include "GLCxx/gl.h"
#include <string>

namespace GLCxx {

void report(std::string const & filename, int line, std::string const & msg = "");

}

#define GLREPORT(msg) ::GLCxx::report(__FILE__, __LINE__, msg)
