#include "Common/gl.h"
#include "Common/File.h"
#include "GLApp/GLApp.h"
#include "Shader/Program.h"

struct Test : public GLApp::GLApp {
	float angle;
	std::shared_ptr<Shader::Program> shaderProgram;

	Test() : GLApp(), angle(0.) {}
	
	virtual void init() {
		GLApp::init();
		glClearColor(.5, .75, .75, 1.);
	
		std::string shaderCode = Common::File::read("test.shader");
		std::vector<Shader::Shader> shaders = {
			Shader::VertexShader(std::vector<std::string>{"#define VERTEX_SHADER\n", shaderCode}),
			Shader::FragmentShader(std::vector<std::string>{"#define FRAGMENT_SHADER\n", shaderCode})
		};
		shaderProgram = std::make_shared<Shader::Program>(shaders);
	}
	
	virtual void resize(int width, int height) {
		GLApp::resize(width, height);
		float aspectRatio = (float)width / (float)height;
		float zNear = .1;
		float zFar = 100;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-aspectRatio * zNear, aspectRatio * zNear, -zNear, zNear, zNear, zFar);
	}
	
	virtual void update() {
		GLApp::update();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0, 0, -2);
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
		
		angle += .01;
	}
};

GLAPP_MAIN(Test)
