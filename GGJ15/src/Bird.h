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
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;

class Bird : public Agent
{
public:
	Bird (Vec2f pos, Vec2f vel, float angle, float radius)
	: Agent (pos, vel, radius),
	  orientation (angle)
	
	{
		shader = gl::GlslProg (loadResource (BIRD_VERT), loadResource (BIRD_FRAG));
	}
	
	void update()
	{
		//position += velocity;
		
	}
	
	void draw()
	{
		
		shader.bind();
		shader.uniform ("resolution", Vec2f ((float) getWindowWidth(), (float) getWindowHeight()));
		Vec2f normedPosition = getPosition() / Vec2f ((float) getWindowWidth(), (float) getWindowHeight()) * 2.f - Vec2f (1.f, 1.f);
		normedPosition.y *= -1.f;
		shader.uniform ("normedPosition", normedPosition);
						
		gl::pushMatrices();
		gl::color (1.0, 0., 0.);
		gl::translate (getPosition());
		gl::rotate (orientation);
		gl::begin (GL_TRIANGLE_STRIP);
		gl::vertex (Vec3f (getRadius(), getRadius(), sin(getElapsedSeconds() * 20.) * getRadius() ));
		gl::vertex (Vec3f (0., -getRadius(), 0.));
		gl::vertex (Vec3f (0., getRadius() / 2., 0.));
		gl::vertex (Vec3f (0., -getRadius(), 0.));
		gl::vertex (Vec3f (-getRadius(), getRadius(), -sin(getElapsedSeconds() * 20.) * getRadius()));
		gl::end();
		gl::rotate (-orientation);
		gl::translate (-getPosition());
		gl::popMatrices();
		shader.unbind();
	}
	
	void setOrientation (float o)
	{
		orientation = o;
	}
	float getOrientation()
	{
		return orientation;
	}
private:
	float orientation;
	gl::GlslProg shader;
};

#endif /* defined(__GGJ15__Bird__) */
