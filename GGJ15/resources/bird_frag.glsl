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
    vec2 position = gl_TexCoord[0].ts /20.;
    
    vec3 color = vec3(0.,0.,1.);
    
    if(position.x < -.5)
        color  = vec3(1.,1.,0.);
    
    if( distance(position,vec2(-.2,0.2)) <.2 || distance(position,vec2(-.2,-.2)) <.2)
       color = vec3(1.);
    
    if( distance(position,vec2(-.2,0.2)) <.05 || distance(position,vec2(-.2,-.2)) <.05)
        color = vec3(0.);
    
    gl_FragColor = vec4 (color, 1.);
}