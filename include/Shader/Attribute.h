#pragma once

#include "Shader/Buffer.h"

namespace Shader {

struct Attribute {
	//this ....
	//int glslType = {};	//GL_FLOAT_VEC2, GL_FLOAT_MAT3x3, etc ... used by getters I think? idk?  
	//... seems redundant to these two ...	
	int type = {};		//GL_FLOAT etc
	int size = {};		// dimension of the data ... 1 2 3 4
	
	int stride = {};
	intptr_t offset = {};
	bool normalize = {};
	int arraySize = 1;	//e.g. 3 for "attribute float attr[3];"
	
	int loc = {};		//attribute location of our Program
	
	Buffer * buffer = {};

	Attribute() {}
	
	Attribute(
		//int glslType_,
		int type_,
		int size_,
		int stride_,
		intptr_t offset_,
		bool normalize_,
		int arraySize_,
		int loc_,
		Buffer * buffer_ = {}
	) :	type(type_),
		size(size_),
		stride(stride_),
		offset(offset_),
		normalize(normalize_),
		arraySize(arraySize_),
		loc(loc_),
		buffer(buffer_)
	{
	}

#if 0
	Attribute(
		Program const & program,
		int loc_,
		Buffer * buffer_
	) {
		loc = loc_;
#error here	
		//derive the rest from program attrib loc
		int maxLen = {};
		glGetIntegerv(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLen);
		int bufSize = maxLen+1;
		std::vector<GLchar> name(bufSize);
		GLsizei length = {};
		GLint arraySize = {};
		GLenum glslType = {};
		glGetActiveAttrib(program(), loc, bufSize, &length, &arraySize, &glslType, name.data());
	}

	Attribute(
		Program const & program,
		std::string const & name,
		Buffer * buffer_
	) {
		loc = program.getAttribLocation(name);
#error here	
		//derive the rest from program attrib loc
	}
#endif

	//assumes the buffer is bound
	void setPointer() const;

	//assumes the buffer is bound
	void enable() const;
	
	//assumes the buffer is bound
	void disable() const;

	// shorthand for binding to the associated buffer, setPointer, and enable
	void set() const;
};

}
