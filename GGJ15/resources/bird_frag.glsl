#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
varying vec3 v;

const float pi = 3.14159265359;


void main( void )
{
	vec2 position = (gl_FragCoord.xy / resolution.xy) * 2. - 1.;
	vec2 vPosition = (v.xy / resolution.xy) * 2. - 1.;
	// write Total Color:
	float d = distance (position, vPosition.xy);
	gl_FragColor = vec4 (vec3 (vPosition.x), 1.0);//Iamb + Idiff + Ispec;
	
}