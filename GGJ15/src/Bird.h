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

using namespace ci;

class Bird
{
public:
	Bird (Vec2f pos, Vec2f vel, float angle)
	: position (pos), velocity (vel), orientation (angle)
	{
	}
	
	void update()
	{
		position += velocity;
	}
	
	void draw()
	{
		gl::pushMatrices();
		gl::translate (position * -1.f);
		gl::rotate (Vec3f (0., 0., orientation));
		gl::translate (position);
		gl::color (1., 0., 0.);
		gl::begin (GL_TRIANGLES);
		gl::vertex (position.x + 10., position.y + 3., 0.);
		gl::vertex (position.x + 10., position.y + 8., 0.);
		gl::vertex (position.x + 0., position.y + 0., 0.);
		gl::end();
		gl::begin (GL_TRIANGLES);
		gl::vertex (position.x + 20., position.y + 0., 0.);
		gl::vertex (position.x + 10., position.y + 8., 0.);
		gl::vertex (position.x + 10., position.y + 3., 0.);
		gl::end();
		gl::popMatrices();
	}
	
private:
	Vec2f position;
	Vec2f velocity;
	float orientation;
};

#endif /* defined(__GGJ15__Bird__) */
