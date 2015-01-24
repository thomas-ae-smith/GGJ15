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
using namespace ci::app;

class Bird : public Agent
{
public:
	Bird (Vec2f pos, Vec2f vel, float angle, float radius)
	:orientation (angle)
	{
        Agent(pos, vel, radius);
	}
	
	void update()
	{
		//position += velocity;
	}
	
	void draw()
	{
		console() << getPosition().x <<" "<<getPosition().y<<" "<<getRadius()<<std::endl;
		gl::pushMatrices();
		gl::color (1.0, 0., 0.);
		gl::translate (getPosition());
		gl::rotate (orientation);
		gl::begin (GL_TRIANGLE_STRIP);
		gl::vertex (Vec3f (-getRadius(), -getRadius(), 0.));
		gl::vertex (Vec3f (0., getRadius(), 0.));
		gl::vertex (Vec3f (getRadius(), -getRadius(), 0.));
		gl::end();
		gl::rotate (-orientation);
		gl::translate (-getPosition());
		gl::popMatrices();
	}
	
private:
	float orientation;
};

#endif /* defined(__GGJ15__Bird__) */
