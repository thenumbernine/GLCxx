#pragma once

#ifdef MACOSX
#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#include <string>
#include <memory>

namespace Shader {

struct GLHandle {
protected:
	typedef ::GLhandleARB HandleType;

	struct Contents {
		HandleType handle;
		
		//contents receives a native handle and assumes control of it
		//it then frees the handle upon its own destruction
		//Contents itself is only held by GLHandle as a shared_ptr
		Contents(HandleType handle_) {
			handle = handle_;
		}
		~Contents() {
			glDeleteObjectARB(handle);
		}
	};
	
	std::shared_ptr<Contents> contents;
public:
	GLHandle();
	GLHandle(HandleType handleContents);
	GLHandle(const GLHandle& handle);
	
	GLHandle& operator=(const GLHandle& handle);
	virtual ~GLHandle();

	HandleType operator()() const;
	static std::string getLog(HandleType handle);
};

};
