#pragma once 

#include "Shader/Wrapper.h"
#include "Common/Exception.h"
#include "GLApp/gl.h"

namespace Shader {

struct BufferWrapperInfo {
	static void getivFn(GLuint a, GLenum b, GLint* c) {
		throw Common::Exception() << "here";
		//glGetShaderiv(a,b,c);
	}

	static void getInfoLogFn(GLuint a, GLint b, GLint* c, GLchar* d) {
		throw Common::Exception() << "here";
		//glGetShaderInfoLog(a,b,c,d);
	}

	static void deleteFn(GLuint a) {
		glDeleteBuffers(1, &a);
	}
};

struct Buffer : public Wrapper<BufferWrapperInfo> {
	using Super = Wrapper;

	Buffer();
	Buffer(int size, uint8_t * data = nullptr);
	Buffer(Buffer const & buffer);
	Buffer& operator=(Buffer const & buffer);

	void setData(int size, uint8_t * data, int usage = GL_STATIC_DRAW) const;
	void updateData(int size, uint8_t * data, int offset = 0) const;
	void bind() const;
	void unbind() const;
	
	//I guess unless I template Buffer then I'll need the vtable to hide the target
	virtual int getTarget() const = 0; 
};

template<int target>
struct BufferType : public Buffer {
	using Super = Buffer;
	
	virtual int getTarget() const { return target; }

	BufferType() {}
	BufferType(BufferType const & buffer) { this->operator=(buffer); }
	BufferType& operator=(BufferType const & buffer) {
		contents = buffer.contents;
		return *this;
	}
	
	BufferType(int size, uint8_t * data = nullptr) : Super(size, data) {}
};

using ArrayBuffer = BufferType<GL_ARRAY_BUFFER>;
using ElementArrayBuffer = BufferType<GL_ELEMENT_ARRAY_BUFFER>;
using PixelPackBuffer = BufferType<GL_PIXEL_PACK_BUFFER>;
using PixelUnpackBuffer = BufferType<GL_PIXEL_UNPACK_BUFFER>;

}
