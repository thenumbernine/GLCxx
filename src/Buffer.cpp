#include "GLCxx/Buffer.h"
#include "GLCxx/gl.h"

namespace GLCxx {

Buffer::Buffer() {}

Buffer::Buffer(Buffer const & buffer) {
	operator=(buffer);
}

Buffer::Buffer(Buffer && buffer) {
	operator=(buffer);
}

Buffer & Buffer::operator=(Buffer const & buffer) {
	contents = buffer.contents;
	target = buffer.target;
	return *this;
}

Buffer & Buffer::operator=(Buffer && buffer) {
	contents = buffer.contents;
	target = buffer.target;
	return *this;
}

Buffer::Buffer(int target_, int size, void const * data, int usage)
: Super(genBuffer()), target(target_)
{
	setData(size, data, usage);
}
	
void Buffer::setData(int size, void const * data, int usage) const {
	bind();
	glBufferData(target, size, data, usage);
	unbind();
}

void Buffer::updateData(int size, void const * data, int offset) const {
	if (!data) return;      //glBufferData spec says it can handle NULL, glBufferSubData doesn't
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
