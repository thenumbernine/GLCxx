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

	template<GLenum pname>	Texture const	& setParam(GLfloat param) 						const	{ glTexParameterf(target, pname, param); return *this; }
	template<GLenum pname>	Texture 		& setParam(GLfloat param) 								{ glTexParameterf(target, pname, param); return *this; }
							Texture const	& setParam(GLenum const pname, GLfloat param)	const	{ glTexParameterf(target, pname, param); return *this; }
							Texture 	 	& setParam(GLenum const pname, GLfloat param) 			{ glTexParameterf(target, pname, param); return *this; }
	
	template<GLenum pname>	Texture const	& setParam(GLint param)							const	{ glTexParameteri(target, pname, param); return *this; }
	template<GLenum pname>	Texture 		& setParam(GLint param) 	   							{ glTexParameteri(target, pname, param); return *this; }
							Texture const	& setParam(GLenum const pname, GLint param) 	const	{ glTexParameteri(target, pname, param); return *this; }
							Texture 	 	& setParam(GLenum const pname, GLint param) 			{ glTexParameteri(target, pname, param); return *this; }

	template<GLenum pname>	Texture const	& setParam(GLfloat const * param) 						const	{ glTexParameterfv(target, pname, param); return *this; }
	template<GLenum pname>	Texture 		& setParam(GLfloat const * param) 								{ glTexParameterfv(target, pname, param); return *this; }
							Texture const	& setParam(GLenum const pname, GLfloat const * param)	const	{ glTexParameterfv(target, pname, param); return *this; }
							Texture 	 	& setParam(GLenum const pname, GLfloat const * param) 			{ glTexParameterfv(target, pname, param); return *this; }
	
	template<GLenum pname>	Texture const	& setParam(GLint const * param)							const	{ glTexParameteriv(target, pname, param); return *this; }
	template<GLenum pname>	Texture 		& setParam(GLint const * param) 	   							{ glTexParameteriv(target, pname, param); return *this; }
							Texture const	& setParam(GLenum const pname, GLint const * param) 	const	{ glTexParameteriv(target, pname, param); return *this; }
							Texture 	 	& setParam(GLenum const pname, GLint const * param) 			{ glTexParameteriv(target, pname, param); return *this; }
	
	template<GLenum pname>	Texture const	& setParamI(GLint const * param)						const	{ glTexParameterIiv(target, pname, param); return *this; }
	template<GLenum pname>	Texture 		& setParamI(GLint const * param) 	   							{ glTexParameterIiv(target, pname, param); return *this; }
							Texture const	& setParamI(GLenum const pname, GLint const * param) 	const	{ glTexParameterIiv(target, pname, param); return *this; }
							Texture 	 	& setParamI(GLenum const pname, GLint const * param) 			{ glTexParameterIiv(target, pname, param); return *this; }
	
	template<GLenum pname>	Texture const	& setParamIu(GLuint const * param)						const	{ glTexParameterIuiv(target, pname, param); return *this; }
	template<GLenum pname>	Texture 		& setParamIu(GLuint const * param) 	   							{ glTexParameterIuiv(target, pname, param); return *this; }
							Texture const	& setParamIu(GLenum const pname, GLuint const * param) 	const	{ glTexParameterIuiv(target, pname, param); return *this; }
							Texture 	 	& setParamIu(GLenum const pname, GLuint const * param) 			{ glTexParameterIuiv(target, pname, param); return *this; }

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
