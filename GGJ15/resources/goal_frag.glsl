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
	//mod(orientation / 45, 8);
    vec2 position = gl_TexCoord[0].ts ;
    float c = abs(position.y - sin(position.x + 25. * time));
	
	vec2 scrPos = (gl_FragCoord.xy / resolution.xy) * 2. - 1.;
	
	float ang = (mod(time * 200., 100.)/100.) * 2. * pi;
	float r = 0.04;
	float x = normedGoalPosition.x + r * cos (ang);
	float y = normedGoalPosition.y + r * sin (ang);
	float d = 1. - distance (scrPos, vec2(x, y)) * 10. * (abs(sin(time*3.))*0.3 + 0.7);
	
	float ang2 = (mod(time * 200., 100.)/100.) * 2. * pi;
	float r2 = 0.04;
	float x2 = normedGoalPosition.x + r2 * cos (ang2);
	float y2 = normedGoalPosition.y + r2 * sin (ang2);
	float d2 = 1. - distance (scrPos, vec2(x2, y2)) * 10. * (abs(sin(time*3.5))*0.3 + 0.7);
	
	vec3 c1 = vec3 (0.4, 0.8, 0.7);
	vec3 c2 = vec3 (0.4, 0.8, 0.7);
	
    gl_FragColor = vec4 (c1 * d + (c2 * d2), 1.);
}