#pragma once

#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>
#include <string>

namespace Shader {

class GLHandle {
protected:
	typedef ::GLhandleARB HandleType;
	HandleType handle;

	void reset();
public:
	GLHandle();
	virtual ~GLHandle();

	HandleType getHandle() const { return handle; }

	static std::string getLog(HandleType handle);
};

};

