uniform float time;
uniform vec2 resolution;
varying vec3 N;
varying vec3 v;

void main()
{
	vec4 positionInView = gl_ModelViewMatrix * gl_Vertex;
	v = vec3 (positionInView.x, positionInView.y, positionInView.z);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
