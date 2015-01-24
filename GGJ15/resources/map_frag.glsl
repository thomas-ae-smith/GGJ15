#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec2 normedGoalPosition;
uniform vec2 radius;

uniform vec3 outputColor;

varying vec3 v;
varying vec3 N;



const float pi = 3.14159265359;


void main( void )
{
	vec2 position = (gl_FragCoord.xy / resolution.xy) * 2. - 1.;
	// write Total Color:
	float r = clamp (1. - distance (position, normedGoalPosition + vec2 (0., 0.1*sin(time))) * (10. + abs(sin(time)) * 5.), 0., 1.);
	float g = clamp (1. - distance (position, normedGoalPosition) * (10. + abs(sin(time*1.5)) * 6.), 0., 1.);
	float b = clamp (1. - distance (position, normedGoalPosition) * (10. + abs(sin(time*2.)) * 7.), 0., 1.);

	gl_FragColor = vec4 (vec3(r * 0.7, g * 0.7, b * 0.7), 1.);
	
}