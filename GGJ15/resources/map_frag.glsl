#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform vec2 normedTargetPosition;
uniform int numTargets;
uniform vec2 normedGoalPosition;
uniform float normedTargetCoords [22];
uniform int numBirds;
uniform float normedBirdCoords [24];
uniform float birdOrientations [12];
uniform float birdRules[12];
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

float unnormedPointLineDistance(in vec2 a, in vec2 b, vec2 p)
{
	return abs ( (b.y - a.y) * p.x - (b.x - a.x) * p.y + b.x*a.y - b.y*a.x );
}

void main() {
    vec2 uv = 2. * gl_FragCoord.xy / resolution.xy - 1.;
    vec2 uvs = uv * resolution.xy / max(resolution.x, resolution.y);
    vec3 p = vec3(uvs / 4., 0) + vec3(1., -1.3, 0.);
    p += .2 * vec3(sin(time / 16.), sin(time / 12.),  sin(time / 128.));
    float t = field(p);
    float v = (1. - exp((abs(uv.x) - 1.) * 6.)) * (1. - exp((abs(uv.y) - 1.) * 6.));
    gl_FragColor = mix(.4, 1., v) * vec4(1.8 * t * t * t, 1.2 * t * t, t, 1.0) * 0.7;
	
	
	// Birds
	vec3 birdsC = vec3(0.);
	if (numBirds > 0)
	{
		for (int i = 0; i < numBirds; i++)
		{
			if (birdRules[i] == 1.)
			{
				vec2 birdPos = vec2(normedBirdCoords[i*2], normedBirdCoords[i*2+1]);

				float ang = 0.;
				float offset = float(mod (birdOrientations[i], 90.) == 0.) * 90.;
				ang = ( (mod (birdOrientations[i] + offset, 360.)) / 360.) * 2. * pi;
				float r = 0.1;
				float x = birdPos.x + r * cos (ang);
				float y = birdPos.y + r * sin (ang);
				vec2 point = vec2 (x, y);
				vec2 v = birdPos - point;
				float lineD = clamp (1. - unnormedPointLineDistance (birdPos, point, uv) * 200., 0., 1.);
				//			if (birdOrientations[i], 90. == 0
				float offsetPolarity = float(mod (birdOrientations[i], 180.) < 91.) * 2. - 1.;
				if (birdOrientations[i] == 90.)
				{
					offsetPolarity = -1.;
				}
				if (birdOrientations[i] != 270.)
				{
					lineD *= clamp (1. - abs(distance (uv, birdPos + v * 10. * offsetPolarity)),0.,1.);
				}
				else
				{
					lineD = 0.;
				}
				
				
				
				//float d = clamp (1. - distance (uv, birdPos) * (10. + abs(sin(time)) * 5.), 0., 1.);
				birdsC += vec3  ( lineD);
			}

		}
	}
	
	
//    targets
	vec3 targetsC = vec3(0.);
	if (numTargets > 0)
	{
		for (int i = 0; i < numTargets; i++)
		{
			vec2 targetPos = vec2 (normedTargetCoords[i * 2], normedTargetCoords[(i * 2) + 1]);
			float r = clamp (1. - distance (uv, targetPos) * (10. + abs(sin(time)) * 5.), 0., 1.);
			float g = clamp (1. - distance (uv, targetPos) * (10. + abs(sin(time*1.5)) * 6.), 0., 1.);
			float b = clamp (1. - distance (uv, targetPos) * (10. + abs(sin(time*2.)) * 7.), 0., 1.);
			
			targetsC += vec3(r, g, b);
		}
	}

	
   	//goal
   	float dG = clamp (1. - distance (uv, normedGoalPosition) * 10. + cos(time)/10., 0., 1.) ;
    
    vec3 targetOrbs = targetsC * 1.;
	vec3 birdOrbs = birdsC * 0.9;
   	vec3 goalOrb = vec3(1., .5, .9) * vec3 (dG) * (1. + .25 *cos(10. * time));
    gl_FragColor.xyz = gl_FragColor.xyz  + goalOrb + targetOrbs + birdOrbs;
}

