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
#include <stdlib.h>
#include "Agent.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
#include "cinder/CinderResources.h"
#include "Math.h"

using namespace ci;
using namespace ci::app;

class Bird : public Agent
{
public:
	Bird (Vec2f pos, Vec2f vel, float radius)
	: Agent (pos, vel, radius)
	
	{
		updateOrientationForVelocity (vel);
		#ifdef __APPLE__
			shader = gl::GlslProg (loadResource (BIRD_VERT), loadResource (BIRD_FRAG));
		#elif defined _WIN32 || defined _WIN64
			shader = gl::GlslProg (loadResource (BIRD_VERT,"GLSL"), loadResource (BIRD_FRAG,"GLSL"));
		#endif
        m_r=1.;
        m_g=1.;
        m_b=1.;
        m_move = false;
		m_rightVertex = Vec3f (getRadius(), getRadius(), 1.);
		m_leftVertex = Vec3f (-getRadius(), getRadius(), 1.);
	}
	
	void update()
	{
		float t = sin(float(getElapsedSeconds()) * 10.);
		m_rightVertex.x = getRadius() - (t * 4.);
		m_leftVertex.x = -getRadius() + (t * 4.);
        if(m_move)
		{
			Agent::updatePosition();
			if(!m_noRules)
			{
				m_orientation = m_oriAttr;
			}
		}
	}
    
    void setColor(float r, float g, float b)
    {
        m_r=r;
        m_g=g;
        m_b=b;
    }
    
    void letsMove()
    {
        m_move = true;
    }
	
	void draw()
	{
		shader.bind();
		shader.uniform ("resolution", Vec2f ((float) getWindowWidth(), (float) getWindowHeight()));
		Vec2f normedPosition = getPosition() / Vec2f ((float) getWindowWidth(), (float) getWindowHeight()) * 2.f - Vec2f (1.f, 1.f);
		normedPosition.y *= -1.f;
		shader.uniform ("normedBirdPosition", normedPosition);
		shader.uniform ("time", float(getElapsedSeconds()));
        shader.uniform ("outputColor",Vec3f(m_r, m_g, m_b));
		
		gl::pushMatrices();
		gl::translate (getPosition());
		gl::rotate (m_orientation);
		gl::begin (GL_TRIANGLE_STRIP);
        gl::vertex (m_rightVertex);
		gl::vertex (Vec3f (0., -getRadius(), 1.));
		gl::vertex (Vec3f (0., getRadius() / 2., 1.));
		gl::vertex (m_leftVertex);
		gl::end();
		gl::popMatrices();
		shader.unbind();
	}
	
	void setOrientation (float o)
	{
		m_orientation = o;
	}
	float getOrientation()
	{
		return m_orientation;
	}
	
	void updateOrientationForVelocity (Vec2f direction)
	{
		if (direction.x == 0.f && direction.y == -1.f)
		{
			m_orientation = 0.f;
		}
		else if (direction.x == 1.f && direction.y == -1.f)
		{
			m_orientation = 45.f;
		}
		else if (direction.x == 1.f && direction.y == 0.f)
		{
			m_orientation = 90.f;
		}
		else if (direction.x == 1.f && direction.y == 1.f)
		{
			m_orientation = 125.f;
		}
		else if (direction.x == 0.f && direction.y == 1.f)
		{
			m_orientation = 180.f;
		}
		else if (direction.x == -1.f && direction.y == 1.f)
		{
			m_orientation = 225.f;
		}
		else if (direction.x == -1.f && direction.y == 0.f)
		{
			m_orientation = 270.f;
		}
		else if (direction.x == -1.f && direction.y == -1.f)
		{
			m_orientation = 315.f;
		}
	}
private:
    bool  m_move;
    float m_r,m_g,m_b;
	float m_orientation;
	Vec3f m_rightVertex;
	Vec3f m_leftVertex;
	gl::GlslProg shader;
};

#endif /* defined(__GGJ15__Bird__) */
