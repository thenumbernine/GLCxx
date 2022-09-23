#include "Shader/Attribute.h"
#include "GLApp/gl.h"
#include <map>

namespace Shader {

struct AttributeTypeInfo {
	int type;
	int size;
	int size2;
	AttributeTypeInfo(int type_, int size_, int size2_)
	: type(type_), size(size_), size2(size2_) {}
};

static std::map<int, AttributeTypeInfo> getTypeAndSizeForGLSLType = {
	std::make_pair(GL_FLOAT, 				AttributeTypeInfo(GL_FLOAT, 1, 1)),
	std::make_pair(GL_FLOAT_VEC2,			AttributeTypeInfo(GL_FLOAT, 2, 1)),
	std::make_pair(GL_FLOAT_VEC3,			AttributeTypeInfo(GL_FLOAT, 3, 1)),
	std::make_pair(GL_FLOAT_VEC4,			AttributeTypeInfo(GL_FLOAT, 4, 1)),
	std::make_pair(GL_FLOAT_MAT2,			AttributeTypeInfo(GL_FLOAT, 2, 2)),
	std::make_pair(GL_FLOAT_MAT3,			AttributeTypeInfo(GL_FLOAT, 3, 3)),
	std::make_pair(GL_FLOAT_MAT4,			AttributeTypeInfo(GL_FLOAT, 4, 4)),
	std::make_pair(GL_FLOAT_MAT2x3,			AttributeTypeInfo(GL_FLOAT, 2, 3)),
	std::make_pair(GL_FLOAT_MAT2x4,			AttributeTypeInfo(GL_FLOAT, 2, 4)),
	std::make_pair(GL_FLOAT_MAT3x2,			AttributeTypeInfo(GL_FLOAT, 3, 2)),
	std::make_pair(GL_FLOAT_MAT3x4,			AttributeTypeInfo(GL_FLOAT, 3, 4)),
	std::make_pair(GL_FLOAT_MAT4x2,			AttributeTypeInfo(GL_FLOAT, 4, 2)),
	std::make_pair(GL_FLOAT_MAT4x3,			AttributeTypeInfo(GL_FLOAT, 4, 2)),
	std::make_pair(GL_INT,					AttributeTypeInfo(GL_INT, 1, 1)),
	std::make_pair(GL_INT_VEC2,				AttributeTypeInfo(GL_INT, 2, 1)),
	std::make_pair(GL_INT_VEC3,				AttributeTypeInfo(GL_INT, 3, 1)),
	std::make_pair(GL_INT_VEC4,				AttributeTypeInfo(GL_INT, 4, 1)),
//	std::make_pair(GL_DOUBLE,				AttributeTypeInfo(GL_DOUBLE, 1, 1)),
//	std::make_pair(GL_DOUBLE_VEC2,			AttributeTypeInfo(GL_DOUBLE, 2, 1)),
//	std::make_pair(GL_DOUBLE_VEC3,			AttributeTypeInfo(GL_DOUBLE, 3, 1)),
//	std::make_pair(GL_DOUBLE_VEC4,			AttributeTypeInfo(GL_DOUBLE, 4, 1)),
//	std::make_pair(GL_DOUBLE_MAT2,			AttributeTypeInfo(GL_DOUBLE, 2, 2)),
//	std::make_pair(GL_DOUBLE_MAT3,			AttributeTypeInfo(GL_DOUBLE, 3, 3)),
//	std::make_pair(GL_DOUBLE_MAT4,			AttributeTypeInfo(GL_DOUBLE, 4, 4)),
//	std::make_pair(GL_DOUBLE_MAT2x3,		AttributeTypeInfo(GL_DOUBLE, 2, 3)),
//	std::make_pair(GL_DOUBLE_MAT2x4,		AttributeTypeInfo(GL_DOUBLE, 2, 4)),
//	std::make_pair(GL_DOUBLE_MAT3x2,		AttributeTypeInfo(GL_DOUBLE, 3, 2)),
//	std::make_pair(GL_DOUBLE_MAT3x4,		AttributeTypeInfo(GL_DOUBLE, 3, 4)),
//	std::make_pair(GL_DOUBLE_MAT4x2,		AttributeTypeInfo(GL_DOUBLE, 4, 2)),
//	std::make_pair(GL_DOUBLE_MAT4x3,		AttributeTypeInfo(GL_DOUBLE, 4, 2)),
//	std::make_pair(GL_UNSIGNED_INT,			AttributeTypeInfo(GL_UNSIGNED_INT, 1, 1)),
//	std::make_pair(GL_UNSIGNED_INT_VEC2,	AttributeTypeInfo(GL_UNSIGNED_INT, 2, 1)),
//	std::make_pair(GL_UNSIGNED_INT_VEC3,	AttributeTypeInfo(GL_UNSIGNED_INT, 3, 1)),
//	std::make_pair(GL_UNSIGNED_INT_VEC4,	AttributeTypeInfo(GL_UNSIGNED_INT, 4, 1)),
//	std::make_pair(GL_BOOL,					AttributeTypeInfo(GL_BOOL, 1, 1)),
//	std::make_pair(GL_BOOL_VEC2,			AttributeTypeInfo(GL_BOOL, 2, 1)),
//	std::make_pair(GL_BOOL_VEC3,			AttributeTypeInfo(GL_BOOL, 3, 1)),
//	std::make_pair(GL_BOOL_VEC4,			AttributeTypeInfo(GL_BOOL, 4, 1)),
};

void Attribute::setPointer() const {
	glVertexAttribPointer(
		loc,
		size,
		type,
		normalize ? GL_TRUE : GL_FALSE,
		stride,
		(void const *)offset
	);
}

void Attribute::enable() const {
	glEnableVertexAttribArray(loc);
}
	
void Attribute::disable() const {
	glDisableVertexAttribArray(loc);
}
	
void Attribute::set() const {
	if (buffer) buffer->bind();
	setPointer();
	if (buffer) buffer->unbind();
}

}
