#pragma once

#include "GLCxx/gl.h"
#include "GLCxx/Wrapper.h"
#include "Tensor/Vector.h"	//int3

namespace GLCxx {

struct TextureWrapperInfo {
	static constexpr char const * name = "Texture";
	
	static void getivFn(GLuint a, GLenum b, GLint* c) {
		//glGetTextureiv(a,b,c);
	}

	static void getInfoLogFn(GLuint a, GLint b, GLint* c, GLchar* d) {
		//glGetTextureInfoLog(a,b,c,d);
	}

	static void deleteFn(GLuint a) {
		glDeleteTextures(1, &a);
	}
};

inline GLuint genTexture() {
	GLuint id = {};
	glGenTextures(1, &id);
	return id;
}

struct Texture : public Wrapper<TextureWrapperInfo> {
	using Super = Wrapper;
	
	int target = {};

	Tensor::int3 size;
	int internalFormat = {};
	int format = {};
	int type = {};
	void const * data = {};
	int level = {};
	int border = {};

	Texture() {}
	Texture & operator=(Texture const & shader);
	Texture & operator=(Texture && shader);
	Texture(Texture const & shader);
	Texture(Texture && shader);

	Texture(int target_);

	Texture & bind(int unit = -1);
	Texture const & bind(int unit = -1) const;
	
	Texture & unbind(int unit = -1);
	Texture const & unbind(int unit = -1) const;
	
	Texture const & enable() const;
	Texture const & disable() const;

	Texture & create1D(
		int width,
		int internalFormat,
		int format,
		int type,
		void const * data = {},
		int level = {},
		int border = {}
	);

	Texture & create2D(
		int width_,
		int height_,
		int internalFormat_,
		int format_,
		int type_,
		void const * data = {},
		int level = {},
		int border = {}
	);

	Texture & create3D(
		int width_,
		int height_,
		int depth_,
		int internalFormat_,
		int format_,
		int type_,
		void const * data = {},
		int level = {},
		int border = {}
	);

	template<int k>
	Texture const & setParam(float v) const {
		glTexParameterf(target, k, v);
		return *this;
	}

	//can't default-initialize these to member-variables, so I guess I gotta make a lot of overrides
	Texture const & subImage2D(
		void * data,
		int xoffset,
		int yoffset,
		int width_,
		int height_,
		int format_,
		int type_,
		int target_,
		int level = {}
	) const;

	Texture const & subImage2D(
		void * data,
		int xoffset,
		int yoffset,
		int width_,
		int height_,
		int format_,
		int type_
	) const {
		return subImage2D(data, xoffset, yoffset, width_, height_, format_, type_, target);
	}
	
	Texture const & subImage2D(
		void * data,
		int xoffset,
		int yoffset,
		int width_,
		int height_,
		int format_
	) const {
		return subImage2D(data, xoffset, yoffset, width_, height_, format_, type, target);
	}

	Texture const & subImage2D(
		void * data,
		int xoffset,
		int yoffset,
		int width_,
		int height_
	) const {
		return subImage2D(data, xoffset, yoffset, width_, height_, format, type, target);
	}

	Texture const & subImage2D(
		void * data,
		int xoffset,
		int yoffset
	) const {
		return subImage2D(data, xoffset, yoffset, size(0), size(1), format, type, target);
	}

	Texture const & subImage2D(
		void * data
	) const {
		return subImage2D(data, 0, 0, size(0), size(1), format, type, target);
	}

	Texture const & generateMipmap() const;

	void toCPU(
		void * dest,
		int level = {}
	) const;
};

template<typename ...Params> Texture Texture1D(Params&&... params) { return Texture(GL_TEXTURE_1D, std::forward<Params>(params)...); }
template<typename ...Params> Texture Texture2D(Params&&... params) { return Texture(GL_TEXTURE_2D, std::forward<Params>(params)...); }
template<typename ...Params> Texture Texture3D(Params&&... params) { return Texture(GL_TEXTURE_3D, std::forward<Params>(params)...); }
template<typename ...Params> Texture TextureCube(Params&&... params) { return Texture(GL_TEXTURE_CUBE_MAP, std::forward<Params>(params)...); }

}
