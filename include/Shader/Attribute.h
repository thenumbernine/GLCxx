#pragma once

#include "Shader/Buffer.h"

namespace Shader {

struct Attribute {
	int glslType = {};	//TODO default type or no type?
	int stride = {};
	int offset = {};
	int size = {};		// dimension of the data ... 1 2 3 4
	int type = {};		//GL_FLOAT etc
	bool normalize = {};
	int arraySize = 1;	//e.g. 3 for "attribute float attr[3];"
	int loc = {};		//attribute location of our Program
	Buffer * buffer = nullptr;

	Attribute(
		int glslType_,
		int stride_,
		int offset_,
		int size_,
		int type_,
		bool normalize_,
		int arraySize_,
		Buffer * buffer_ = {}
	) : glslType(glslType_),
		stride(stride_),
		offset(offset_),
		size(size_),
		type(type_),
		normalize(normalize_),
		arraySize(arraySize_),
		buffer(buffer_)
	{
	}

	//assumes the buffer is bound
	void setPointer(int loc, intptr_t offset = 0);
	void setPointer();

	//assumes the buffer is bound
	void enable(int loc);
	void enable();
	
	//assumes the buffer is bound
	void disable(int loc);
	void disable();

	// shorthand for binding to the associated buffer, setPointer, and enable
	void set(int loc);
};

}
