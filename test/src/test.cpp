#include "GLApp/GLApp.h"
#include "GLApp/ViewBehavior.h"
#include "GLCxx/Texture.h"
#include "GLCxx/Program.h"
#include "GLCxx/Attribute.h"
#include "GLCxx/VertexArray.h"
#include "GLCxx/Buffer.h"
#include "GLCxx/Report.h"
#include "GLCxx/gl.h"
#include "Image/Image.h"
#include "Tensor/Tensor.h"
#include "Common/File.h"
#include <chrono>

struct Test : public ::GLApp::ViewBehavior<::GLApp::GLApp> {
	using Super = ::GLApp::ViewBehavior<::GLApp::GLApp>;

	using Clock = std::chrono::high_resolution_clock;
	std::chrono::time_point<Clock> lastTime = Clock::now();

	GLCxx::Program shaderProgram;
	GLCxx::Texture tex;
	GLCxx::VertexArray vao;

	float angle = 0;

	virtual std::string getTitle() const {
		return "GLCxx Test";
	}

	virtual void init(const Init& args) {
		Super::init(args);

		glClearColor(.5, .75, .75, 1.);
		viewFrustum->pos.z = 3.;

		Image::Image image(Tensor::int2(256, 256), nullptr, 4);
		//TODO Image ctor via lambda, or Image iterator, or both
		for (int y = 0; y < image.getSize().y; ++y) {
			for (int x = 0; x < image.getSize().x; ++x) {
				for (int ch = 0; ch < image.getChannels(); ++ch) {
					image(x,y,ch) = rand();
				}
			}
		}

		//TODO Texture create2D via ctor, and create2D via Image
		tex = GLCxx::Texture2D()
			.bind()
			.create2D(image.getSize().x, image.getSize().y, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, image.getGrid()->v)
			.setParam<GL_TEXTURE_MIN_FILTER>(GL_NEAREST)
			.setParam<GL_TEXTURE_MAG_FILTER>(GL_LINEAR)
			.setParam<GL_TEXTURE_WRAP_S>(GL_REPEAT)
			.setParam<GL_TEXTURE_WRAP_T>(GL_REPEAT)
			.unbind();

		std::string glslVersion = ::GLCxx::Program::getVersionPragma();
		shaderProgram = GLCxx::Program(
			// vertex code
			std::vector<std::string>{
				glslVersion,	//first
				R"(
uniform mat4 mvMat, projMat;
in vec3 pos, color;
out vec2 posv;
out vec4 colorv;
void main() {
	posv = pos.xy;
	vec4 vtxWorld = mvMat * vec4(pos, 1.);
	gl_Position = projMat * vtxWorld;
	colorv = vec4(color, 1.) + sin(30. * vtxWorld);
}
)",
			},
			// fragment code
			std::vector<std::string>{
				glslVersion,	//first
				R"(
in vec2 posv;
in vec4 colorv;
out vec4 colorf;
uniform sampler2D tex;
void main() {
	vec2 texcoord = posv.xy;
	vec4 texcolor = texture(tex, texcoord);
	colorf = colorv * texcolor + .1 * sin(gl_FragCoord / 5.);
}
)",
			}
		);
		shaderProgram.setUniform<int>("tex", 0);

		vao = GLCxx::VertexArray(std::vector<GLCxx::Attribute>{
				//infer attribute properties from the shader program's attribute info
				GLCxx::Attribute(shaderProgram, "pos", GLCxx::ArrayBuffer(Tensor::float3x3{
					{0, 1.25, 0},
					{-1, -.75, 0},
					{1, -.75, 0}
				})),
				GLCxx::Attribute(shaderProgram, "color", GLCxx::ArrayBuffer(Tensor::float3x3{
					{1,0,0},
					{0,1,0},
					{0,0,1}
				}))
			},
			GLCxx::ElementArrayBuffer(Tensor::uint3{0,1,2})
		);
	}

	virtual void onUpdate() {
		std::chrono::time_point<Clock> thisTime = Clock::now();
		float deltaTime = 1e-9 * (double)std::chrono::duration_cast<std::chrono::nanoseconds>(thisTime - lastTime).count();
		lastTime = thisTime;

		Super::onUpdate();

		view->mvMat = view->mvMat * Tensor::rotate<float>(angle, Tensor::float3(0, 1, 0));

		shaderProgram
			.use()
			.setUniformMatrix<4>("projMat", &view->projMat.x.x, true)
			.setUniformMatrix<4>("mvMat", &view->mvMat.x.x, true);

		tex.bind();
		vao.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		vao.unbind();
		tex.bind();

		shaderProgram.done();

		angle += deltaTime * 360;	//1 revolution per second
	}
};

GLAPP_MAIN(Test)
