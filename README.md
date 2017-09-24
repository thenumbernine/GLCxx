### A simple OpenGL shader library

requires my Common C++ library found [here](https://github.com/thenumbernine/Common)

example:

	std::vector<Shader::Shader> shaders = {
		Shader::VertexShader(vertexShaderCode),
		Shader::FragmentShader(fragmentShaderCode)
	};
	program = std::make_shared<Shader::Program>(shaders);
	program->link()
		.setUniform<int>("texSampler", 0)
		.setUniform<float>("alpha", .5)
		.done();

	...

	program->use();

	program->done();
