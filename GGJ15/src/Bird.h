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
#include "cinder/CinderResources.h"

using namespace ci;
using namespace ci::app;

class Bird : public Agent
{
public:
	Bird (Vec2f pos, Vec2f vel, float angle, float radius)
	: Agent (pos, vel, radius),
	  orientation (angle)
	
	{
		#ifdef __APPLE__
			shader = gl::GlslProg (loadResource (BIRD_VERT), loadResource (BIRD_FRAG));
		#elif defined _WIN32 || defined _WIN64
			shader = gl::GlslProg (loadResource (BIRD_VERT,"GLSL"), loadResource (BIRD_FRAG,"GLSL"));
		#endif
        m_r=1.;
        m_g=1.;
        m_b=1.;
	}
	
	void update()
	{
        setPosition(getPosition() + getVelocity());
	}
    
    void setColor(float r, float g, float b)
    {
        m_r=r;
        m_g=g;
        m_b=b;
    }
	
	void draw()
	{
		shader.bind();
		shader.uniform ("resolution", Vec2f ((float) getWindowWidth(), (float) getWindowHeight()));
		Vec2f normedPosition = getPosition() / Vec2f ((float) getWindowWidth(), (float) getWindowHeight()) * 2.f - Vec2f (1.f, 1.f);
		normedPosition.y *= -1.f;
		shader.uniform ("normedPosition", normedPosition);
        shader.uniform ("outputColor",Vec3f(m_r, m_g, m_b));
        
		gl::pushMatrices();
		gl::color(m_r,m_g,m_b);
		gl::translate (getPosition());
		gl::rotate (orientation);
		gl::begin (GL_TRIANGLE_STRIP);
        gl::vertex (Vec3f (getRadius(), getRadius(), 1.));
		gl::vertex (Vec3f (0., -getRadius(), 1.));
		gl::vertex (Vec3f (0., getRadius() / 2., 1.));
//		gl::vertex (Vec3f (0., -getRadius(), 1.));
		gl::vertex (Vec3f (-getRadius(), getRadius(), 1.));
		gl::end();
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
    float m_r,m_g,m_b;
	float orientation;
	gl::GlslProg shader;
};

#endif /* defined(__GGJ15__Bird__) */
