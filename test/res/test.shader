varying vec4 colorv;

#ifdef VERTEX_SHADER
void main() {
	vec4 vtxWorld = gl_ModelViewMatrix * gl_Vertex;
	gl_Position = gl_ProjectionMatrix * vtxWorld;
	colorv = gl_Color + sin(30. * vtxWorld);
}
#endif	//VERTEX_SHADER

#ifdef FRAGMENT_SHADER
void main() {
	gl_FragColor = colorv + .1 * sin(gl_FragCoord / 5.);
}
#endif	//FRAGMENT_SHADER
