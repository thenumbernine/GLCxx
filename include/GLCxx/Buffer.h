#pragma once 

#include "GLCxx/Wrapper.h"
#include "GLCxx/gl.h"
#include "Common/Exception.h"

namespace GLCxx {

struct BufferWrapperInfo {
	static constexpr char const * name = "Buffer";

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

	Buffer();
	
	Buffer(Buffer const & buffer);
	Buffer(Buffer && buffer);
	
	Buffer& operator=(Buffer const & buffer);
	Buffer& operator=(Buffer && buffer);
	
	Buffer(int target_);
	
	Buffer(int target_, int size, void const * data = nullptr, int usage = GL_STATIC_DRAW);

	template<typename T>
	Buffer(int target_, T const & t, int usage = GL_STATIC_DRAW)
	: Super(genBuffer()), target(target_)
	{
		setData(sizeof(T), &t, usage);
	}

	// will this specialized overload be hit before the generic T case?
	// or will this cause "ambiguous resolution" errors?
	// so far outlook not so good
	template<typename T>
	Buffer(int target_, std::vector<T> & t, int usage = GL_STATIC_DRAW) {
		setData(t.size() * sizeof(T[0]), t.data(), usage);
	}

	void setData(int size, void const * data, int usage = GL_STATIC_DRAW) const;
	void updateData(int size, void const * data, int offset = 0) const;
	
	template<typename T>
	void updateData(T const & t, int offset = 0) const {
		updateData(sizeof(T), &t, offset);
	}

	void bind() const;
	void unbind() const;

protected:
	static GLuint genBuffer() {
		GLuint id = {};
		glGenBuffers(1, &id);
		return id;
	}
};

template<typename ...Params> Buffer ArrayBuffer(Params&&... params) { return Buffer(GL_ARRAY_BUFFER, std::forward<Params>(params)...); }
template<typename ...Params> Buffer ElementArrayBuffer(Params&&... params) { return Buffer(GL_ELEMENT_ARRAY_BUFFER, std::forward<Params>(params)...); }
template<typename ...Params> Buffer PixelPackBuffer(Params&&... params) { return Buffer(GL_PIXEL_PACK_BUFFER, std::forward<Params>(params)...); }
template<typename ...Params> Buffer PixelUnpackBuffer(Params&&... params) { return Buffer(GL_PIXEL_UNPACK_BUFFER, std::forward<Params>(params)...); }
}
