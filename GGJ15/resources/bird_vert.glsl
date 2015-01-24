uniform float time;
uniform vec2 resolution;
varying vec3 N;
varying vec3 v;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
