#include "GLApp/GLApp.h"
#include "GLApp/ViewBehavior.h"
#include "GLCxx/Program.h"
#include "GLCxx/Attribute.h"
#include "GLCxx/VertexArray.h"
#include "GLCxx/Buffer.h"
#include "GLCxx/Report.h"
#include "GLCxx/gl.h"
#include "Tensor/Tensor.h"
#include "Common/File.h"
#include <chrono>

//#define USE_VAO

struct Test : public ::GLApp::ViewBehavior<::GLApp::GLApp> {
	using Super = ::GLApp::ViewBehavior<::GLApp::GLApp>;
	
	using Clock = std::chrono::high_resolution_clock;
	std::chrono::time_point<Clock> lastTime = Clock::now();
	
	std::shared_ptr<GLCxx::Program> shaderProgram;
	
	float angle = 0;

	virtual const char* getTitle() {
		return "GLCxx Test";
	}

	GLCxx::Buffer posBuf, colorBuf, indexBuf;
	GLCxx::Attribute posAttr, colorAttr;
	GLCxx::VertexArray vao;

	virtual void init(const Init& args) {
		Super::init(args);
		
		glClearColor(.5, .75, .75, 1.);
		viewFrustum->pos(2) = 3.;

		using float33 = Tensor::Tensor<float, Tensor::Lower<3>, Tensor::Lower<3>>;
		posBuf = GLCxx::ArrayBuffer(float33{
			{0, 1.25, 0},
			{-1, -.75, 0},
			{1, -.75, 0}
		});
		colorBuf = GLCxx::ArrayBuffer(float33{
			{1,0,0},
			{0,1,0},
			{0,0,1}
		});
		indexBuf = GLCxx::ElementArrayBuffer(Tensor::uint3{0,1,2});

		std::string version = "#version 460\n";
		std::string shaderCode = Common::File::read("test.shader");
		shaderProgram = std::make_shared<GLCxx::Program>(
			// vertex code
			std::vector<std::string>{
				version,	//first
				"#define VERTEX_SHADER\n",
				shaderCode,
			},
			// fragment code
			std::vector<std::string>{
				version,	//first
				"#define FRAGMENT_SHADER\n",
				shaderCode,
			}
		);
GLREPORT("here");		

		//infer attribute properties from the shader program's attribute info
		posAttr = GLCxx::Attribute(*shaderProgram, "pos", &posBuf);
GLREPORT("here");		
		colorAttr = GLCxx::Attribute(*shaderProgram, "color", &colorBuf);
GLREPORT("here");		

#ifdef USE_VAO
GLREPORT("here");		
		vao = GLCxx::VertexArray(std::vector<GLCxx::Attribute>{posAttr, colorAttr});
GLREPORT("here");		
		vao.bind();
GLREPORT("here");		
		for (auto const & attr : vao.attrs) {
			//attr.set();
GLREPORT("here");		
			attr.enable();
GLREPORT("here");		
			attr.buffer->bind();
GLREPORT("here");		
			attr.setPointer();
GLREPORT("here");		
			attr.buffer->unbind();
GLREPORT("here");		
		}
		//indexBuf.bind();
		// this + vao is crashing it
		//Tensor::uint3 indexes = {0,1,2};
		//indexBuf.updateData(indexes);
		vao.unbind();
GLREPORT("here");		
		//posBuf.unbind();	//TODO static per-templated-buffer unbin()
		//indexBuf.unbind();
#else
		posAttr.buffer->bind();
		posAttr.setPointer();
		posAttr.buffer->unbind();
		
		colorAttr.buffer->bind();
		colorAttr.setPointer();
		colorAttr.buffer->unbind();
#endif
	}

	virtual void onUpdate() {
GLREPORT("onUpdate begin");

		std::chrono::time_point<Clock> thisTime = Clock::now();
		float deltaTime = 1e-9 * (double)std::chrono::duration_cast<std::chrono::nanoseconds>(thisTime - lastTime).count();
		lastTime = thisTime;
		
		Super::onUpdate();
		glMatrixMode(GL_MODELVIEW);
		glRotatef(angle,0,1,0);
		
		shaderProgram->use();
	
		float m[16];
		glGetFloatv(GL_PROJECTION_MATRIX, m);
		glUniformMatrix4fv(shaderProgram->getUniformLocation("projectionMatrix"), 1, GL_FALSE, m);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glUniformMatrix4fv(shaderProgram->getUniformLocation("modelViewMatrix"), 1, GL_FALSE, m);
#ifdef USE_VAO
		vao.bind();
		//vao.enableAttrs();
		indexBuf.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		indexBuf.unbind();
		//vao.disableAttrs();
		vao.unbind();
#else
		posAttr.enable();
		colorAttr.enable();
		indexBuf.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		indexBuf.unbind();
		posAttr.disable();
		colorAttr.disable();
#endif
		
		shaderProgram->done();
		
		angle += deltaTime * 360;	//1 revolution per second

GLREPORT("onUpdate end");
	}
};

GLAPP_MAIN(Test)
