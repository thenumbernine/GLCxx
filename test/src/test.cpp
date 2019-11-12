#include "Shader/Program.h"
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
	
	virtual void init() {
		Super::init();
		glClearColor(.5, .75, .75, 1.);
		viewFrustum->dist = 3.;
	
		std::string shaderCode = Common::File::read("test.shader");
		std::vector<Shader::Shader> shaders = {
			Shader::VertexShader(std::vector<std::string>{"#define VERTEX_SHADER\n", shaderCode}),
			Shader::FragmentShader(std::vector<std::string>{"#define FRAGMENT_SHADER\n", shaderCode})
		};
		shaderProgram = std::make_shared<Shader::Program>(shaders);
	}
	
	virtual void update() {
		std::chrono::time_point<Clock> thisTime = Clock::now();
		float deltaTime = 1e-9 * (double)std::chrono::duration_cast<std::chrono::nanoseconds>(thisTime - lastTime).count();
		lastTime = thisTime;
		
		Super::update();
		glMatrixMode(GL_MODELVIEW);
		glRotatef(angle,0,1,0);
		shaderProgram->use();
		glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glVertex3f(0, 1.25,0);
		glColor3f(0,1,0);
		glVertex3f(-1,-.75,0);
		glColor3f(0,0,1);
		glVertex3f(1,-.75,0);
		glEnd();
		shaderProgram->done();
		
		angle += deltaTime * 360;	//1 revolution per second
	}
};

GLAPP_MAIN(Test)
