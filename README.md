### A simple OpenGL shader library

Requires my Common C++ library found [here](https://github.com/thenumbernine/Common)

Example:

```
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
```

TODO
- add in a Texture wrapper class as well
- and a lot of the other wrappers already present in my js and lua gl libraries.
- then rename this project from "Shader" to just "GL" or something.
