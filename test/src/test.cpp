#include "Shader/Program.h"
#include "Shader/Attribute.h"
#include "Shader/VertexArray.h"
#include "Shader/Buffer.h"
#include "GLApp/gl.h"
#include "GLApp/GLApp.h"
#include "GLApp/ViewBehavior.h"
#include "Tensor/Tensor.h"
#include "Common/File.h"
#include <chrono>

//#define USE_VAO

struct Test : public ::GLApp::ViewBehavior<::GLApp::GLApp> {
	using Super = ::GLApp::ViewBehavior<::GLApp::GLApp>;
	
	using Clock = std::chrono::high_resolution_clock;
	std::chrono::time_point<Clock> lastTime = Clock::now();
	
	std::shared_ptr<Shader::Program> shaderProgram;
	
	float angle = 0;

	virtual const char* getTitle() {
		return "Shader Test";
	}

	Shader::Buffer posBuf, colorBuf, indexBuf;
	Shader::Attribute posAttr, colorAttr;
	Shader::VertexArray vao;

	virtual void init(const Init& args) {
		Super::init(args);
		
		glClearColor(.5, .75, .75, 1.);
		viewFrustum->pos(2) = 3.;

		using float33 = Tensor::Tensor<float, Tensor::Lower<3>, Tensor::Lower<3>>;
		posBuf = Shader::ArrayBuffer(float33{
			{0, 1.25, 0},
			{-1, -.75, 0},
			{1, -.75, 0}
		});
		colorBuf = Shader::ArrayBuffer(float33{
			{1,0,0},
			{0,1,0},
			{0,0,1}
		});
		indexBuf = Shader::ElementArrayBuffer(Tensor::int3{0,1,2});

		std::string version = "#version 460\n";
		std::string shaderCode = Common::File::read("test.shader");
		shaderProgram = std::make_shared<Shader::Program>(
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

		//infer attribute properties from the shader program's attribute info
		posAttr = Shader::Attribute(*shaderProgram, "pos", &posBuf);
		colorAttr = Shader::Attribute(*shaderProgram, "color", &colorBuf);

#ifdef USE_VAO
		vao = Shader::VertexArray(std::vector<Shader::Attribute>{posAttr, colorAttr});
		vao.bind();
		for (auto const & attr : vao.attrs) {
			attr.buffer->bind();
			attr.enable();
			attr.set();
		}
		indexBuf.bind();
		// this + vao is crashing it
		//Tensor::int3 indexes = {0,1,2};
		//indexBuf.updateData(sizeof(indexes), indexes.v, 0);
		vao.unbind();
		
		posBuf.unbind();	//TODO static per-templated-buffer unbin()
		indexBuf.unbind();
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
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
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
	}
};

GLAPP_MAIN(Test)
