#pragma once

#include "Shader/Shader.h"
#include <list>

namespace Shader {

struct Program : public GLHandle {
	typedef GLHandle Super;

protected:
	//all attached shaders 
	std::list<Shader> attached;
public:
	
	Program();
	Program(const Program& program);
	Program& operator=(const Program& program);

	Program(std::vector<Shader>& shaders);
	
	Program& attach(const Shader& shader);
	Program& link();

	template<int shaderType>
	Program& attachShader(std::vector<std::string>& sources) {
		ShaderType<shaderType> shader;
		shader.setSources(sources);
		attach(shader);
		return *this;
	}

	std::string getAllLogs();

	Program& use();
	Program& done();	//useNone for this.  had to think of a clever new name.
	static void useNone();

	int getUniformLocation(const std::string& name);

	template<typename T>
	Program& setUniform(const std::string& name, T value);
	
	template<typename T>
	Program& setUniform(const std::string& name, T value1, T value2);
};

};

