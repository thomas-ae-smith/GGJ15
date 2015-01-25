#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec2 normedTargetPosition;
uniform int numTargets;
uniform vec2 normedGoalPosition;
uniform float normedTargetCoords [12];
uniform vec2 radius;

uniform vec3 outputColor;

varying vec3 v;
varying vec3 N;



const float pi = 3.14159265359;


void main( void )
{
	vec2 position = (gl_FragCoord.xy / resolution.xy) * 2. - 1.;
	
	//background
	float x = (mod (time*100., resolution.x) / resolution.x) * 2. - 1.;
	float y = (mod (time*100., resolution.y) / resolution.y) * 2. - 1.;
	float x2 = (mod (time*150., resolution.x) / resolution.x) * 2. - 1.;
	float y2 = (mod (time*150., resolution.y) / resolution.y) * 2. - 1.;
	float x3 = -((mod (time*180., resolution.x) / resolution.x) * 2. - 1.);
	float y3 = -((mod (time*180., resolution.y) / resolution.y) * 2. - 1.);
	float pulse = (abs(sin(time * 2.)) * 0.8 + 0.2) * 200.;
 	float yDiff = clamp(1. - abs(position.y - y) * pulse,0.,1.);
	float xDiff = clamp(1. - abs(position.x - x) * pulse,0.,1.);
	
	float yDiff2 = clamp(1. - abs(position.y - y2) * pulse,0.,1.);
	float xDiff2 = clamp(1. - abs(position.x - x2) * pulse,0.,1.);
	
	float yDiff3 = clamp(1. - abs(position.y - y3) * pulse,0.,1.);
	float xDiff3 = clamp(1. - abs(position.x - x3) * pulse,0.,1.);
	
	//targets
	vec3 targetsC = vec3(0.);
	if (numTargets > 0)
	{
		for (int i = 0; i < numTargets; i++)
		{
			vec2 targetPos = vec2 (normedTargetCoords[i * 2], normedTargetCoords[(i * 2) + 1]);
			float r = clamp (1. - distance (position, targetPos) * (10. + abs(sin(time)) * 5.), 0., 1.);
			float g = clamp (1. - distance (position, targetPos) * (10. + abs(sin(time*1.5)) * 6.), 0., 1.);
			float b = clamp (1. - distance (position, targetPos) * (10. + abs(sin(time*2.)) * 7.), 0., 1.);
			
			targetsC += vec3(r, g, b);
		}
	}
	
	
	
	//goal
	float dG = clamp (1. - distance (position, normedGoalPosition) * 10., 0., 1.);
	
	vec3 goalOrb = vec3 (dG);
	vec3 targetOrbs = targetsC * 0.7;
	vec3 line = vec3 (0.3, 0.6, 0.8) * (yDiff + xDiff + yDiff2 + xDiff2 + xDiff3 + yDiff3) * 0.5;
	
	gl_FragColor = vec4 (line + targetOrbs + goalOrb, 1.);
	
}