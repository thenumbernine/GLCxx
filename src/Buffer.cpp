#include "Shader/Buffer.h"
#include "GLApp/gl.h"

namespace Shader {

Buffer::Buffer() {}

Buffer::Buffer(Buffer const & buffer) {
	this->operator=(buffer);
}

Buffer & Buffer::operator=(Buffer const & buffer) {
	contents = buffer.contents;
	return *this;
}

static GLuint genBuffer() {
	GLuint id = {};
	glGenBuffers(1, &id);
	return id;
}

Buffer::Buffer(int size, uint8_t * data)
: Super(genBuffer())
{
	setData(size, data);
}
	
void Buffer::setData(int size, uint8_t * data, int usage) const {
	bind();
	glBufferData(getTarget(), size, data, usage);
	unbind();
}

void Buffer::updateData(int size, uint8_t * data, int offset) const {
	bind();
	glBufferSubData(getTarget(), offset, size, data);
	unbind();
}

void Buffer::bind() const {
	glBindBuffer(getTarget(), (*this)());
}

void Buffer::unbind() const {
	glBindBuffer(getTarget(), 0);
}

}
