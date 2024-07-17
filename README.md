### OpenGL Class Library

[![Donate via Stripe](https://img.shields.io/badge/Donate-Stripe-green.svg)](https://buy.stripe.com/00gbJZ0OdcNs9zi288)<br>

Requires 
- [Common](https://github.com/thenumbernine/Common)
- [Tensor](https://github.com/thenumbernine/Tensor)

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
