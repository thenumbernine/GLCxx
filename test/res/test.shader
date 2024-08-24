#ifdef VERTEX_SHADER
uniform mat4 mvMat, projMat;
in vec3 pos, color;
out vec2 posv;
out vec4 colorv;
void main() {
	posv = pos.xy;
	vec4 vtxWorld = mvMat * vec4(pos, 1.);
	gl_Position = projMat * vtxWorld;
	colorv = vec4(color, 1.) + sin(30. * vtxWorld);
}
#endif	//VERTEX_SHADER

#ifdef FRAGMENT_SHADER
in vec2 posv;
in vec4 colorv;
out vec4 colorf;
uniform sampler2D tex;
void main() {
	vec2 texcoord = posv.xy;
	vec4 texcolor = texture(tex, texcoord);
	colorf = colorv * texcolor + .1 * sin(gl_FragCoord / 5.);
}
#endif	//FRAGMENT_SHADER
