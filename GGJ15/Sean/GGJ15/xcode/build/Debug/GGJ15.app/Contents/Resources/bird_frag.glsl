#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec2 normedBirdPosition;
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
	float d = distance (scrPos, normedBirdPosition) * 20.;
	
	float y = normedBirdPosition.y + sin(time * 3.) * 0.02;
	float yDiff1 = clamp (1. - abs(scrPos.y - y) * 100., 0., 1.);
	
    gl_FragColor = vec4 (vec3 (3., 1., 3.)*yDiff1 + outputColor , 1.);
}