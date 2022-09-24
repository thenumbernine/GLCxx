#include "Shader/Program.h"
#include "Shader/Attribute.h"
#include "Shader/VertexArray.h"
#include "Shader/Buffer.h"
#include "GLApp/gl.h"
#include "GLApp/GLApp.h"
#include "GLApp/ViewBehavior.h"
#include "Common/File.h"

#include <chrono>

struct Test : public ::GLApp::ViewBehavior<::GLApp::GLApp> {
	using Super = ::GLApp::ViewBehavior<::GLApp::GLApp>;
	
	using Clock = std::chrono::high_resolution_clock;
	std::chrono::time_point<Clock> lastTime = Clock::now();
	
	std::shared_ptr<Shader::Program> shaderProgram;
	
	float angle = 0;

	virtual const char* getTitle() {
		return "Shader Test";
	}

	Shader::ArrayBuffer posBuf, colorBuf;
	Shader::Attribute posAttr, colorAttr;
	Shader::VertexArray vao;

	virtual void init(const Init& args) {
		Super::init(args);
		
		glClearColor(.5, .75, .75, 1.);
		viewFrustum->dist = 3.;

		
		using float3 = Tensor::Vector<float, 3>;
		posBuf = Shader::ArrayBuffer(std::vector<float3>{
			{0, 1.25, 0},
			{-1, -.75, 0},
			{1, -.75, 0}
		});
		colorBuf = Shader::ArrayBuffer(std::vector<float3>{
			{1,0,0},
			{0,1,0},
			{0,0,1}
		});
#if 0  //goal:
		posBuf = Shader::ArrayBuffer(Tensor::Tensor<float, Tensor::Lower<3>, Tensor::Lower<3>>{
			{0, 1.25, 0},
			{-1, -.75, 0},
			{1, -.75, 0}
		});
		colorBuf = Shader::ArrayBuffer(Tensor::Tensor<float, Tensor::Lower<3>, Tensor::Lower<3>>{
			{1,0,0},
			{0,1,0},
			{0,0,1}
		});
#endif

		std::string version = "#version 460\n";
		std::string shaderCode = Common::File::read("test.shader");
		shaderProgram = std::make_shared<Shader::Program>(std::vector<Shader::Shader>{
			Shader::VertexShader(std::vector<std::string>{
				version,	//first
				"#define VERTEX_SHADER\n",
				shaderCode,
			}),
			Shader::FragmentShader(std::vector<std::string>{
				version,	//first
				"#define FRAGMENT_SHADER\n",
				shaderCode,
			})
		});

		posAttr = Shader::Attribute(
			GL_FLOAT,
			3,
			0,
			0,
			false,
			1,
			shaderProgram->getAttribLocation("pos"),
			&posBuf
		);
		colorAttr = Shader::Attribute(
			GL_FLOAT,
			3,
			0,
			0,
			false,
			1,
			shaderProgram->getAttribLocation("color"),
			&colorBuf
		);
	
		vao.attrs = {posAttr, colorAttr};
		vao.bind();
		vao.enableAttrs();
		for (auto const & attr : vao.attrs) {
			attr.set();	//requires attr.loc to be set
		}
		vao.unbind();
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
		
		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		vao.unbind();
		
		shaderProgram->done();
		
		angle += deltaTime * 360;	//1 revolution per second
	}
};

GLAPP_MAIN(Test)
