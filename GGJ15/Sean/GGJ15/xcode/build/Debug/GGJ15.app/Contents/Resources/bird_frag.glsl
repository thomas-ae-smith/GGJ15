#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec2 normedBirdPosition;
uniform vec2 radius;
varying vec3 v;
varying vec3 N;

uniform vec3 eyePos;

uniform vec3 lPos;
uniform float shininess;
uniform vec3 specular;
uniform vec3 diffuse;
uniform vec3 ambient;

uniform float diffuseIntensity;
uniform float specularRadius;
uniform float specularIntensity;

const float pi = 3.14159265359;


void main( void )
{
	vec2 position = (gl_FragCoord.xy / resolution.xy) * 2. - 1.;
	// write Total Color:
	vec2 vPosition = ((((v.xy + resolution.xy) / 2.) / resolution.xy) * 2. - 1.) * 2.;
	float t = abs (sin (time));
	float r =  1. - distance (normedBirdPosition, vPosition) * t * 10.;
	float g =  1. - distance (normedBirdPosition, vPosition) * (1. - t) * 10.;
	float b =  1. - distance (normedBirdPosition, vPosition) * t * 1.2 * 10.;
	
	
	vec3 L = normalize(lPos - v);
	vec3 V = normalize(eyePos - v);
	vec3 R = normalize(-reflect(L,N));
	
	vec4 Iamb = vec4 (ambient, 1.0);
	
	vec4 Idiff = vec4 (vec3 (diffuseIntensity), 1.0) * max(dot(N,L), 0.0);
	
	float f = dot (V, N);
	
	float sr = (1. - specularRadius) * 194. + 6.;
	vec4 Ispec = vec4 (vec3 (specularIntensity), 1.0)
	* pow(max(dot(R,V),0.0),sr);
	
	Ispec = clamp(Ispec, 0.0, 1.0);
	
	gl_FragColor = vec4 ((Iamb.xyz + Idiff.xyz + Ispec.xyz) + (1.-f), 1.0);
	
}