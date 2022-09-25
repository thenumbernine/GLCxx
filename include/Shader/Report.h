#pragma once

#include "GLApp/gl.h"
#include <string>

namespace Shader {

void report(std::string const & filename, int line, std::string const & msg = "");

}

#define GLREPORT(msg) ::Shader::report(__FILE__, __LINE__, msg)
