#include "GLCxx/Texture.h"
#include "Common/Exception.h"

namespace GLCxx {

Texture & Texture::operator=(Texture const & shader) {
	contents = shader.contents;
	target = shader.target;
	return *this;
}

Texture & Texture::operator=(Texture && shader) {
	contents = shader.contents;
	target = shader.target;
	return *this;
}

Texture::Texture(Texture const & shader) {
	operator=(shader);
}

Texture::Texture(Texture && shader) {
	operator=(shader);
}

Texture::Texture(int target_)
: Super(genTexture()), target(target_)
{
	bind();
}

Texture & Texture::bind(int unit) {
	if (unit >= 0) {
		glActiveTexture(GL_TEXTURE0 + unit);
	}
	glBindTexture(target, (*this)());
	return *this;
}

Texture const & Texture::bind(int unit) const {
	if (unit >= 0) {
		glActiveTexture(GL_TEXTURE0 + unit);
	}
	glBindTexture(target, (*this)());
	return *this;
}

Texture & Texture::unbind(int unit) {
	if (unit >= 0) {
		glActiveTexture(GL_TEXTURE0 + unit);
	}
	glBindTexture(target, 0);
	return *this;
}

Texture const & Texture::unbind(int unit) const {
	if (unit >= 0) {
		glActiveTexture(GL_TEXTURE0 + unit);
	}
	glBindTexture(target, 0);
	return *this;
}

Texture const & Texture::enable() const {
	glEnable(target);
	return *this;
}

Texture const & Texture::disable() const {
	glDisable(target);
	return *this;
}

Texture & Texture::create1D(
	int width_,
	int internalFormat_,
	int format_,
	int type_,
	void const * data_,
	int level_,
	int border_
) {
	size = {width_, 1, 1};
	internalFormat = internalFormat_;
	format = format_;
	type = type_;
	data = data_;
	level = level_;
	border = border_;
	glTexImage1D(
		target,
		level,
		internalFormat,
		size.x,
		border,
		format,
		type,
		data);
	return *this;
}

Texture & Texture::create2D(
	int width_,
	int height_,
	int internalFormat_,
	int format_,
	int type_,
	void const * data_,
	int level_,
	int border_
) {
	size = {width_,  height_, 1};
	internalFormat = internalFormat_;
	format = format_;
	type = type_;
	data = data_;
	level = level_;
	border = border_;
	glTexImage2D(
		target,
		level,
		internalFormat,
		size.x,
		size.y,
		border,
		format,
		type,
		data);
	return *this;
}

Texture & Texture::create3D(
	int width_,
	int height_,
	int depth_,
	int internalFormat_,
	int format_,
	int type_,
	void const * data_,
	int level_,
	int border_
) {
	size = {width_, height_, depth_};
	internalFormat = internalFormat_;
	format = format_;
	type = type_;
	data = data_;
	level = level_;
	border = border_;
	glTexImage3D(
		target,
		level,
		internalFormat,
		size.x,
		size.y,
		size.z,
		border,
		format,
		type,
		data);
	return *this;
}

Texture const & Texture::subImage2D(
	void * data,
	int xoffset,
	int yoffset,
	int width_,
	int height_,
	int format_,
	int type_,
	int target_,
	int level
) const {
	glTexSubImage2D(
		target_,
		level,
		xoffset,
		yoffset,
		width_,
		height_,
		format_,
		type_,
		data);
	return *this;
}

Texture const & Texture::generateMipmap() const {
	glGenerateMipmap(target);
	return *this;
}

void Texture::toCPU(void * dest, int level) const {
	if (!dest) {
		throw Common::Exception() << "dest is null";
	}
	bind();
	glGetTexImage(target, level, format, type, dest);
}

}
