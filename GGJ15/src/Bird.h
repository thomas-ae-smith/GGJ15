//
//  Bird.h
//  GGJ15
//
//  Created by Sean Soraghan on 23/01/2015.
//
//

#ifndef __GGJ15__Bird__
#define __GGJ15__Bird__

#include <stdio.h>
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;

class Bird
{
public:
	Bird (Vec2f pos, Vec2f vel, float angle, float r)
	: position (pos), velocity (vel), orientation (angle), radius (r)
	{
	}
	
	void update()
	{
		//position += velocity;
	}
	
	void draw()
	{
		gl::translate (position);
		gl::rotate (orientation);
		gl::begin (GL_TRIANGLE_STRIP);
		gl::vertex (Vec3f (-radius, -radius, 0.));
		gl::vertex (Vec3f (0., radius, 0.));
		gl::vertex (Vec3f (radius, -radius, 0.));
		gl::end();
		gl::rotate (-orientation);
		gl::translate (-position);
	}
	
private:
	Vec2f position;
	Vec2f velocity;
	float orientation;
	float radius;
};

#endif /* defined(__GGJ15__Bird__) */
