#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const float pi = 3.14159265359;


void main( void )
{
	
	
	// write Total Color:
	gl_FragColor = vec4 (vec3 (1.), 1.0);//Iamb + Idiff + Ispec;
	
}