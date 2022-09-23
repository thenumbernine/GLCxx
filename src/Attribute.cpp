#include "Shader/Attribute.h"
#include "GLApp/gl.h"

namespace Shader {

void Attribute::setPointer(int loc, intptr_t offset) {
	glVertexAttribPointer(
		loc,
		size,
		type,
		normalize ? GL_TRUE : GL_FALSE,
		stride,
		(void const *)offset
	);
}

void Attribute::setPointer() {
	setPointer(loc);
}
	
void Attribute::enable(int loc) {
	glEnableVertexAttribArray(loc);
}
	
void Attribute::enable() {
	enable(loc); 
}
	
void Attribute::disable(int loc) {
	glDisableVertexAttribArray(loc);
}
	
void Attribute::disable() { 
	disable(loc); 
}

void Attribute::set(int loc) {
	if (buffer) buffer->bind();
	setPointer(loc);
	if (buffer) buffer->unbind();
}

}
