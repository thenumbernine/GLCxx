#include "Shader/VertexArray.h"

namespace Shader {

VertexArray::VertexArray(VertexArray const & vao) {
	this->operator=(vao);
}

VertexArray & VertexArray::operator=(VertexArray const & vao) {
	contents = vao.contents;
	return *this;
}

static GLuint genVertexArray() {
	GLuint id = {};
	glGenVertexArrays(1, &id);
	return id;
}

VertexArray::VertexArray()
: Super(genVertexArray())
{
}


}
