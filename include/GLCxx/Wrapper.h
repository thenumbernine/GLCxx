#pragma once

#include "GLCxx/gl.h"
#include "Common/Exception.h"
#include <string>
#include <memory>
#include <vector>
#include <iostream>

namespace GLCxx {

template<typename Info_>
struct Wrapper {
protected:
	using Info = Info_;
	using HandleType = ::GLuint;

	struct Contents {
		HandleType handle;
		
		//contents receives a native handle and assumes control of it
		//it then frees the handle upon its own destruction
		//Contents itself is only held by Wrapper as a shared_ptr
		Contents(HandleType handle_) {
			handle = handle_;
		}
		~Contents() {
			Info::deleteFn(handle);
		}
	};
	
	std::shared_ptr<Contents> contents;

public:
	
	Wrapper() {}
	
	Wrapper(HandleType handleContents)
	: contents(std::make_shared<Contents>(handleContents))
	{}
	
	Wrapper(Wrapper const & handle) {
		operator=(handle);
	}
	
	Wrapper(Wrapper && handle) {
		operator=(handle);
	}
	
	Wrapper & operator=(Wrapper const & handle) {
		contents = handle.contents;
		return *this;
	}
	
	Wrapper & operator=(Wrapper && handle) {
		contents = handle.contents;
		return *this;
	}

	virtual ~Wrapper() {}

	HandleType operator()() const {
		if (!contents.get()) return {};
		return contents->handle;
	}

	template<GLenum pname>
	GLint geti() const {
		GLint result = {};
		Info::getivFn((*this)(), pname, &result);
		return result;
	}

	std::string getLog() const {
		GLint length = geti<GL_INFO_LOG_LENGTH>();
std::cout << "log length: " << length << std::endl;		
		if (length <= 0) return std::string();

		std::vector<GLchar> log(length);
		Info::getInfoLogFn((*this)(), length, nullptr, log.data());
std::cout << "log real length: " << length << std::endl;		

		std::string logStr = std::string(log.begin(), log.end());
std::cout << "log str: " << logStr << std::endl;		
		return logStr;
	}
};

}
