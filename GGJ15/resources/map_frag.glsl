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
    
//    targets
//    vec3 targetsC = vec3 (0.);
//    for (int i=0; i < numTargets; i+= 2)
//    {
//        vec2 targetPos = vec2(normedTargetPositions[i], normedTargetPositions[i+1]);
//        float r = clamp (1. - distance (position, targetPos) * (10. + abs(sin(time)) * 5.), 0., 1.);
//        float g = clamp (1. - distance (position, targetPos) * (10. + abs(sin(time*1.5)) * 6.), 0., 1.);
//        float b = clamp (1. - distance (position, targetPos) * (10. + abs(sin(time*2.)) * 7.), 0., 1.);
//        targetsC += vec3 (.0, .5, .1);
//    }

    
   	//goal
   	float dG = clamp (1. - distance (uv, normedGoalPosition) * 10. + cos(time)/10., 0., 1.) ;
    
//    vec3 targetOrbs = targetsC * 0.7;
   	vec3 goalOrb = vec3(.7, .2, .6) * vec3 (dG) * (1. + .25 *cos(10. * time));
    gl_FragColor.xyz = gl_FragColor.xyz  + goalOrb; // + targetOrbs;
}