#pragma once

#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>
#include <string>

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

