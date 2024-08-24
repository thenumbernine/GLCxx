#include "GLCxx/Program.h"
#include "Common/Exception.h"
#include <vector>
#include <regex>

namespace GLCxx {

Program::Program() {}

Program::Program(Program const & program) {
	operator=(program);
}

Program::Program(Program && program) {
	operator=(program);
}

Program & Program::operator=(Program const & program) {
	contents = program.contents;
	attached = program.attached;
	return *this;
}

Program & Program::operator=(Program && program) {
	contents = program.contents;
	attached = program.attached;
	return *this;
}

Program::Program(std::vector<Shader> & shaders)
: Super(glCreateProgram())
{
	init(shaders);
}

Program::Program(std::vector<Shader>&& shaders)
: Super(glCreateProgram())
{
	init(shaders);
}

Program::Program(
	std::vector<std::string> const & vertexShaderCode,
	std::vector<std::string> const & fragmentShaderCode
)
: Super(glCreateProgram())
{
	init(std::vector<Shader>{
		VertexShader(vertexShaderCode),
		FragmentShader(fragmentShaderCode),
	});
}

Program::Program(
	std::vector<std::string> && vertexShaderCode,
	std::vector<std::string> && fragmentShaderCode
)
: Super(glCreateProgram())
{
	init(std::vector<Shader>{
		VertexShader(vertexShaderCode),
		FragmentShader(fragmentShaderCode),
	});
}

Program::Program(
	std::string const & vertexShaderCode,
	std::string const & fragmentShaderCode
)
: Super(glCreateProgram())
{
	init(std::vector<Shader>{
		VertexShader(std::vector<std::string>{vertexShaderCode}),
		FragmentShader(std::vector<std::string>{fragmentShaderCode}),
	});
}

Program::Program(
	std::string && vertexShaderCode,
	std::string && fragmentShaderCode
)
: Super(glCreateProgram())
{
	init(std::vector<Shader>{
		VertexShader(std::vector<std::string>{vertexShaderCode}),
		FragmentShader(std::vector<std::string>{fragmentShaderCode}),
	});
}

void Program::init(std::vector<Shader> const & shaders) {
	for (auto const & shader : shaders) {
		attach(shader);
	}
	link();

	//TODO?
	//store uniform locations
	//store attribute locations
}

void Program::init(std::vector<Shader> && shaders) {
	for (auto const & shader : shaders) {
		attach(shader);
	}
	link();

	//TODO?
	//store uniform locations
	//store attribute locations
}

Program & Program::attach(Shader const & shader) {
	glAttachShader((*this)(), shader());
	attached.push_back(shader);
	return *this;
}

Program & Program::link() {
	GLint status = geti<GL_LINK_STATUS>();

	//don't link twice!!! intel drivers are crashing when you do that
	if (status != 0) throw Common::Exception() << "won't link, program " << (*this)() << " already has link status " << status;

	glLinkProgram((*this)());

	GLint linked = geti<GL_LINK_STATUS>();
	if (!linked) {
		throw Common::Exception() << "failed to link program.\n" << getLog();
	}
	for (auto & shader : attached) {
		glDetachShader((*this)(), shader());
	}
	return *this;
}

Program & Program::attachShader(int shaderType, std::vector<std::string> & sources) {
	Shader shader(shaderType);
	shader.setSources(sources);
	attach(shader);
	return *this;
}

Program & Program::use() {
	glUseProgram((*this)());
	return *this;
}

Program const & Program::use() const {
	glUseProgram((*this)());
	return *this;
}

Program & Program::done() {
	Program::useNone();
	return *this;
}

Program const & Program::done() const {
	Program::useNone();
	return *this;
}

void Program::useNone() {
	glUseProgram(0);
}

int Program::getUniformLocation(std::string const & name) const {
	return glGetUniformLocation((*this)(), name.c_str());
}

int Program::getAttribLocation(std::string const & name) const {
	return glGetAttribLocation((*this)(), name.c_str());
}

template<>
Program & Program::setUniform<int>(std::string const & name, int value) {
	glUniform1i(getUniformLocation(name), value);
	return *this;
}

template<>
Program & Program::setUniform<bool>(std::string const & name, bool value) {
	glUniform1i(getUniformLocation(name), value);
	return *this;
}

template<>
Program & Program::setUniform<float>(std::string const & name, float value) {
	glUniform1f(getUniformLocation(name), value);
	return *this;
}

template<>
Program & Program::setUniform<float>(std::string const & name, float value1, float value2) {
	glUniform2f(getUniformLocation(name), value1, value2);
	return *this;
}

template<>
Program & Program::setUniform<float>(std::string const & name, float value1, float value2, float value3) {
	glUniform3f(getUniformLocation(name), value1, value2, value3);
	return *this;
}

std::string Program::getVersionPragma() {
	auto strptr = glGetString(GL_SHADING_LANGUAGE_VERSION);
	if (strptr == nullptr) throw Common::Exception() << "failed to get GL_SHADING_LANGUAGE_VERSION";
	auto version = std::string((char const *)strptr);
	version = std::regex_replace(version, std::regex("\\."), "");
	return std::string("#version ")+version;
}

};
