#include "GLCxx/VertexArray.h"
#include "GLCxx/gl.h"

namespace GLCxx {

static GLuint genVertexArray() {
	GLuint id = {};
	glGenVertexArrays(1, &id);
	return id;
}

VertexArray::VertexArray() {}

VertexArray::VertexArray(VertexArray const & vao) {
	operator=(vao);
}

VertexArray::VertexArray(VertexArray && vao) {
	operator=(vao);
}

VertexArray & VertexArray::operator=(VertexArray const & vao) {
	contents = vao.contents;
	attrs = vao.attrs;
	return *this;
}

VertexArray & VertexArray::operator=(VertexArray && vao) {
	contents = vao.contents;
	attrs = vao.attrs;
	return *this;
}

VertexArray::VertexArray(std::vector<Attribute> const & attrs_) 
: Super(genVertexArray()), attrs(attrs_) {
	bind();
	enableAttrs();
	setAttrs();
	unbind();
}

VertexArray::VertexArray(std::vector<Attribute> && attrs_) 
: Super(genVertexArray()), attrs(attrs_) {
	bind();
	enableAttrs();
	setAttrs();
	unbind();
}

VertexArray::VertexArray(
	std::vector<Attribute> const & attrs_,
	Buffer const & indexBuffer
) : Super(genVertexArray()),
	attrs(attrs_) 
{
	bind();
	enableAttrs();
	setAttrs();
	indexBuffer.bind();
	unbind();
}

VertexArray::VertexArray(
	std::vector<Attribute> && attrs_,
	Buffer const & indexBuffer
) : Super(genVertexArray()),
	attrs(attrs_)
{
	bind();
	enableAttrs();
	setAttrs();
	indexBuffer.bind();
	unbind();
}

}
