#pragma once

#include "GLApp/gl.h"
#include <string>
#include <memory>
#include <vector>

//testing:
#include <iostream>

namespace Shader {

template<typename Info>
struct Wrapper {
protected:
	
	typedef ::GLuint HandleType;

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
	
	Wrapper(const Wrapper& handle) {
		this->operator=(handle);
	}
	
	Wrapper& operator=(const Wrapper& handle) {
		contents = handle.contents;
		return *this;
	}

	virtual ~Wrapper() {}

	HandleType operator()() const {
		if (!contents.get()) return HandleType();
		return contents->handle;
	}

	std::string getLog() const {
		GLint length = 0;
		Info::getivFn((*this)(), GL_INFO_LOG_LENGTH, &length);
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
