#pragma once

#include "GLCxx/Buffer.h"
#include "GLCxx/Program.h"

namespace GLCxx {

struct Attribute {
	int type = {};		//GL_FLOAT etc
	int size = {};		// dimension of the data ... 1 2 3 4
	
	int stride = {};
	intptr_t offset = {};
	bool normalize = {};
	int arraySize = 1;	//e.g. 3 for "attribute float attr[3];"
	
	int loc = {};		//attribute location of our Program

	//should all Attribute objects *always* have associated Buffer objects?
	Buffer * buffer = {};

	Attribute() {}
	
	Attribute(
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
	{}

	Attribute(
		Program const & program,
		int loc_,
		Buffer * buffer_ = {}
	) : loc(loc_),
		buffer(buffer_)
	{
		deriveFromProgramAttr(program);
	}

	Attribute(
		Program const & program,
		std::string const & name,
		Buffer * buffer_ = {}
	) : loc(program.getAttribLocation(name)),
		buffer(buffer_)
	{
		deriveFromProgramAttr(program);
	}

protected:
	void deriveFromProgramAttr(Program const & program);

public:

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
