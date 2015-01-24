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
#include "Agent.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;

class Bird : Agent
{
public:
	Bird (Vec2f pos, Vec2f vel, float angle)
	:orientation (angle)
	{
        Agent(pos,vel,2.);
	}
	
	void update()
	{
		//position += velocity;
	}
	
	void draw()
	{
		gl::translate (getPosition());
		gl::rotate (orientation);
		gl::begin (GL_TRIANGLE_STRIP);
		gl::vertex (Vec3f (0., 0., 0.));
		gl::vertex (Vec3f (5., 7., 0.));
		gl::vertex (Vec3f (10., 0., 0.));
		gl::end();
		gl::rotate (-orientation);
		gl::translate (-getPosition());
	}
	
private:
	float orientation;
};

#endif /* defined(__GGJ15__Bird__) */
