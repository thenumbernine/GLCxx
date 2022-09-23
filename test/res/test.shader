#ifdef VERTEX_SHADER
uniform mat4 modelViewMatrix, projectionMatrix;
in vec3 pos, color;
out vec4 colorv;
void main() {
	vec4 vtxWorld = modelViewMatrix * vec4(pos, 1.);
	gl_Position = projectionMatrix * vtxWorld;
	colorv = vec4(color, 1.) + sin(30. * vtxWorld);
}
#endif	//VERTEX_SHADER

#ifdef FRAGMENT_SHADER
in vec4 colorv;
out vec4 colorf;
void main() {
	colorf = colorv + .1 * sin(gl_FragCoord / 5.);
}
#endif	//FRAGMENT_SHADER
