#pragma once

#include "Shader/Shader.h"
#include <list>

namespace Shader {

class Program : public GLHandle {
protected:
	//only the shaders owned by this object -- used via attachVertexShader/attachFragmentShader
	std::list<std::shared_ptr<Shader>> ownedShaders;
	
	//all attached shaders -- used for logging
	// you can even attach other shaders via attach() and they end up here
	std::list<HandleType> attachedHandles;
public:

	Program();

	void attach(HandleType extHandle);
	void attach(const Shader &shader);

	void attachShader(std::string filename, int shaderType, std::string prefix = std::string());
	void attachVertexShader(std::string filename, std::string prefix = std::string());
	void attachFragmentShader(std::string filename, std::string prefix = std::string());

	void link();

	std::string getAllLogs();

	void use();
	static void useNone();

	int getUniformLocation(std::string name);

	template<typename T>
	void setUniform(std::string name, T value);
	
	template<typename T>
	void setUniform(std::string name, T value1, T value2);
};

};

