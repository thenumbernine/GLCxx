#pragma once

#if PLATFORM_OSX

//for GLhandleARB, etc
#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>

#include <OpenGL/gl.h>

#elif PLATFORM_LINUX

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

#elif PLATFORM_MSVC || PLATFORM_MINGW || PLATFORM_CLANG_WIN

#include <windows.h>
//#define GL_GLEXT_PROTOTYPES
#include "GL/glew.h"
#include <GL/gl.h>
//#include "GL/glext.h"

#endif	//PLATFORM_*
