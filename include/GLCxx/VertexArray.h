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
	
	VertexArray & operator=(VertexArray const & vao);
	VertexArray & operator=(VertexArray && vao);
	
	VertexArray(std::vector<Attribute> const & attrs_);
	VertexArray(std::vector<Attribute> && attrs_);
	
	VertexArray(std::vector<Attribute> const & attrs_, Buffer const & indexBuffer);
	VertexArray(std::vector<Attribute> && attrs_, Buffer const & indexBuffer);

	VertexArray & setAttrs() {
		for (auto const & attr : attrs) {
			attr.set();
		}
		return *this;
	}

	VertexArray const & setAttrs() const {
		for (auto const & attr : attrs) {
			attr.set();
		}
		return *this;
	}

	VertexArray & bind() {
		glBindVertexArray((*this)());
		return *this;
	}
	
	VertexArray const & bind() const {
		glBindVertexArray((*this)());
		return *this;
	}

	VertexArray & unbind() {
		glBindVertexArray(0);
		return *this;
	}
	
	VertexArray const & unbind() const {
		glBindVertexArray(0);
		return *this;
	}

	VertexArray & enableAttrs() {
		for (auto const & attr : attrs) {
			attr.enable();
		}
		return *this;
	}
	
	VertexArray const & enableAttrs() const {
		for (auto const & attr : attrs) {
			attr.enable();
		}
		return *this;
	}

	VertexArray & disableAttrs() {
		for (auto const & attr : attrs) {
			attr.disable();
		}
		return *this;
	}

	VertexArray const & disableAttrs() const {
		for (auto const & attr : attrs) {
			attr.disable();
		}
		return *this;
	}
};

}
