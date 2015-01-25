#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float normedTargetPositions[14];
uniform int numTargets;
uniform vec2 normedGoalPosition;
uniform vec2 radius;

uniform vec3 outputColor;

varying vec3 v;
varying vec3 N;



const float pi = 3.14159265359;


//void main( void )
//{
//	vec2 position = (gl_FragCoord.xy / resolution.xy) * 2. - 1.;
//
//	//background
//	float x = (mod (time*100., resolution.x) / resolution.x) * 2. - 1.;
//	float y = (mod (time*100., resolution.y) / resolution.y) * 2. - 1.;
//	float x2 = (mod (time*150., resolution.x) / resolution.x) * 2. - 1.;
//	float y2 = (mod (time*150., resolution.y) / resolution.y) * 2. - 1.;
//	float x3 = -((mod (time*180., resolution.x) / resolution.x) * 2. - 1.);
//	float y3 = -((mod (time*180., resolution.y) / resolution.y) * 2. - 1.);
//	float pulse = (abs(sin(time * 2.)) * 0.8 + 0.2) * 200.;
// 	float yDiff = clamp(1. - abs(position.y - y) * pulse,0.,1.);
//	float xDiff = clamp(1. - abs(position.x - x) * pulse,0.,1.);
//
//	float yDiff2 = clamp(1. - abs(position.y - y2) * pulse,0.,1.);
//	float xDiff2 = clamp(1. - abs(position.x - x2) * pulse,0.,1.);
//
//	float yDiff3 = clamp(1. - abs(position.y - y3) * pulse,0.,1.);
//	float xDiff3 = clamp(1. - abs(position.x - x3) * pulse,0.,1.);
//
//	//targets
//	vec3 targetsC = vec3 (0.);
//	for (int i=0; i < numTargets; i+= 2)
//	{
//		vec2 targetPos = vec2(normedTargetPositions[i], normedTargetPositions[i+1]);
//		float r = clamp (1. - distance (position, targetPos) * (10. + abs(sin(time)) * 5.), 0., 1.);
//		float g = clamp (1. - distance (position, targetPos) * (10. + abs(sin(time*1.5)) * 6.), 0., 1.);
//		float b = clamp (1. - distance (position, targetPos) * (10. + abs(sin(time*2.)) * 7.), 0., 1.);
//		targetsC += vec3 (r, g, b);
//	}
//
//
//
//	//goal
//	float dG = clamp (1. - distance (position, normedGoalPosition) * 10., 0., 1.);
//
//	vec3 goalOrb = vec3 (dG);
//	vec3 targetOrbs = targetsC * 0.7;
//	vec3 line = vec3 (0.3, 0.6, 0.8) * (yDiff + xDiff + yDiff2 + xDiff2 + xDiff3 + yDiff3) * 0.5;
//
//	gl_FragColor = vec4 (line + targetOrbs + goalOrb, 1.);
//
//}

// http://www.fractalforums.com/new-theories-and-research/very-simple-formula-for-fractal-patterns/
float field(in vec3 p) {
    float strength = 7. + .03 * log(1.e-6 + fract(sin(time) * 4373.11));
    float accum = 0.;
    float prev = 0.;
    float tw = 0.;
    for (int i = 0; i < 32; ++i) {
        float mag = dot(p, p);
        p = abs(p) / mag + vec3(-.5, -.4, -1.5);
        float w = exp(-float(i) / 7.);
        accum += w * exp(-strength * pow(abs(mag - prev), 2.3));
        tw += w;
        prev = mag;
    }
    return max(0., 5. * accum / tw - .7);
}

void main() {
    vec2 uv = 2. * gl_FragCoord.xy / resolution.xy - 1.;
    vec2 uvs = uv * resolution.xy / max(resolution.x, resolution.y);
    vec3 p = vec3(uvs / 4., 0) + vec3(1., -1.3, 0.);
    p += .2 * vec3(sin(time / 16.), sin(time / 12.),  sin(time / 128.));
    float t = field(p);
    float v = (1. - exp((abs(uv.x) - 1.) * 6.)) * (1. - exp((abs(uv.y) - 1.) * 6.));
    gl_FragColor = mix(.4, 1., v) * vec4(1.8 * t * t * t, 1.2 * t * t, t, 1.0);
    
   	//goal
   	float dG = clamp (1. - distance (uv, normedGoalPosition) * 10., 0., 1.);
    
   	vec3 goalOrb = vec3 (dG);
    gl_FragColor.xyz = gl_FragColor.xyz  + goalOrb;

    
}