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
    vec2 position = gl_TexCoord[0].ts ;
    float c = abs(position.y - sin(position.x + 25. * time));
    
    gl_FragColor = vec4 (outputColor, 1.);
}