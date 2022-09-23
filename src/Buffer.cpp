#include "Shader/Buffer.h"
#include "GLApp/gl.h"

namespace Shader {

Buffer::Buffer(int target_) : target(target_) {}

Buffer::Buffer(Buffer const & buffer) {
	this->operator=(buffer);
}

Buffer & Buffer::operator=(Buffer const & buffer) {
	contents = buffer.contents;
	target = buffer.target;
	return *this;
}

static GLuint genBuffer() {
	GLuint id = {};
	glGenBuffers(1, &id);
	return id;
}

Buffer::Buffer(int target_, int size, uint8_t const * data, int usage)
: Super(genBuffer()), target(target_)
{
	setData(size, data, usage);
}
	
void Buffer::setData(int size, uint8_t const * data, int usage) const {
	bind();
	glBufferData(target, size, data, usage);
	unbind();
}

void Buffer::updateData(int size, uint8_t const * data, int offset) const {
	bind();
	glBufferSubData(target, offset, size, data);
	unbind();
}

void Buffer::bind() const {
	glBindBuffer(target, (*this)());
}

void Buffer::unbind() const {
	glBindBuffer(target, 0);
}

}
