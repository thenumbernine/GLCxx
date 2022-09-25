#include "Shader/VertexArray.h"

namespace Shader {

static GLuint genVertexArray() {
	GLuint id = {};
	glGenVertexArrays(1, &id);
	return id;
}

VertexArray::VertexArray() 
: Super(genVertexArray())
{}

VertexArray::VertexArray(VertexArray const & vao) {
	operator=(vao);
}

VertexArray::VertexArray(VertexArray && vao) {
	operator=(vao);
}

VertexArray & VertexArray::operator=(VertexArray const & vao) {
	contents = vao.contents;
	return *this;
}

VertexArray & VertexArray::operator=(VertexArray && vao) {
	contents = vao.contents;
	return *this;
}

VertexArray::VertexArray(std::vector<Attribute> const & attrs_) 
: Super(genVertexArray()), attrs(attrs_) {
	setAttrs();
}

VertexArray::VertexArray(std::vector<Attribute> && attrs_) 
: Super(genVertexArray()), attrs(attrs_) {
	setAttrs();
}

}
