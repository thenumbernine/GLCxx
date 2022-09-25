### A simple OpenGL shader library

Requires my Common C++ library found [here](https://github.com/thenumbernine/Common)

Example:

```
	program = std::make_shared<GLCxx::Program>({
		vertexShaderCode,
		fragmentShaderCode
	});
	program->link()
		.setUniform<int>("texSampler", 0)
		.setUniform<float>("alpha", .5)
		.done();

	...

	program->use();

	program->done();
```
