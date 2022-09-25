#pragma once

#include "GLCxx/Wrapper.h"
#include "GLCxx/Attribute.h"
#include "GLCxx/gl.h"
#include <vector>

namespace GLCxx {

struct VertexArrayWrapperInfo {
	static constexpr char const * name = "VertexArray";
	
	static void getivFn(GLuint a, GLenum b, GLint* c) {
		throw Common::Exception() << "here";
		//glGetShaderiv(a,b,c);
	}

	static void getInfoLogFn(GLuint a, GLint b, GLint* c, GLchar* d) {
		throw Common::Exception() << "here";
		//glGetShaderInfoLog(a,b,c,d);
	}

	static void deleteFn(GLuint a) {
		glDeleteVertexArrays(1, &a);
	}
};

struct VertexArray : public Wrapper<VertexArrayWrapperInfo> {
	using Super = Wrapper;

	std::vector<Attribute> attrs;

	VertexArray();
	
	VertexArray(VertexArray const & vao);
	VertexArray(VertexArray && vao);
	
	VertexArray& operator=(VertexArray const & vao);
	VertexArray& operator=(VertexArray && vao);
	
	VertexArray(std::vector<Attribute> const & attrs_);
	VertexArray(std::vector<Attribute> && attrs_);

	void setAttrs() {
		bind();
		for (auto const & attr : attrs) {
			attr.set();
		}
		unbind();
	}
	
	void bind() const {
		glBindVertexArray((*this)());
	}

	void unbind() const {
		glBindVertexArray(0);
	}

	void enableAttrs() const {
		for (auto const & attr : attrs) {
			attr.enable();
		}
	}

	void disableAttrs() const {
		for (auto const & attr : attrs) {
			attr.disable();
		}
	}

	// shorthand for bind + enableAttrs
	void use() const {
		bind();
		enableAttrs();
	}

	// shorthand for unbind + disableAttrs
	void useNone() const {
		disableAttrs();
		unbind();
	}


};

}
