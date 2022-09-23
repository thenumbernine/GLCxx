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

	//TODO make this a member of the BufferWrapperInfo type, to pair it with the glGenBuffer?
	int target = {};

	Buffer(int target_);
	Buffer(int target_, int size, uint8_t const * data = nullptr, int usage = GL_STATIC_DRAW);
	Buffer(Buffer const & buffer);
	Buffer& operator=(Buffer const & buffer);

	void setData(int size, uint8_t const * data, int usage = GL_STATIC_DRAW) const;
	void updateData(int size, uint8_t const * data, int offset = 0) const;
	void bind() const;
	void unbind() const;
};

//TODO no point in this separate class right, as long as I'm putting 'target' as a member variable of the parent.
template<int Target>
struct BufferType : public Buffer {
	using Super = Buffer;

	BufferType() : Super(Target) {}
	BufferType(BufferType const & buffer) { operator=(buffer); }
	BufferType& operator=(BufferType const & buffer) {
		Super::operator=(buffer);
		return *this;
	}
	
	BufferType(int size, uint8_t const * data = nullptr, int usage = GL_STATIC_DRAW) 
	: Super(Target, size, data, usage) {}

	template<typename T>
	BufferType(std::vector<T> const & v, int usage = GL_STATIC_DRAW)
	: Super(Target, sizeof(T) * v.size(), (uint8_t const *)v.data(), usage) {}
};

using ArrayBuffer = BufferType<GL_ARRAY_BUFFER>;
using ElementArrayBuffer = BufferType<GL_ELEMENT_ARRAY_BUFFER>;
using PixelPackBuffer = BufferType<GL_PIXEL_PACK_BUFFER>;
using PixelUnpackBuffer = BufferType<GL_PIXEL_UNPACK_BUFFER>;

}
