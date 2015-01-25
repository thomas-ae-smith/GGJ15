//
//  Agent.h
//  Stephane
//
//  Created by Stephan LB on 23/01/2015.
//
//

#ifndef __Stephane__Agent__
#define __Stephane__Agent__
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
using namespace ci;

#include "Map.h"

class Agent
{
public:
    Agent():m_position(Vec2f(0.,0.)),
            m_velocity(Vec2f(0.,0.)),
            m_radius(0.),
			velMult (1.){}
    
    Agent(Vec2f position, float radius):m_position(position),
                                        m_velocity(Vec2f(0.,0.)),
										m_radius(radius),
										velMult (1.){}
	
    Agent(Vec2f position, Vec2f velocity, float radius):m_position(position),
                                        m_velocity(velocity),
										m_radius(radius),
										velMult (1.){}
    
    void setPosition(Vec2f position)
    {
        m_position = position;
    }
    
    void setPosition(float x, float y)
    {
        m_position = Vec2f(x,y);
    }
    
    Vec2f getPosition()
    {
        return m_position;
    }
    
    void setVelocity(Vec2f velocity)
    {
        m_velocity = velocity;
    }
    
    void setVelocity(float x, float y)
    {
        m_velocity = Vec2f(x,y);
    }
	
	void setSpeedMultiplier(float s)
	{
		velMult = s;
	}
	
    Vec2f getVelocity()
    {
        return m_velocity;
    }
    
    void setRadius(float r)
    {
        m_radius = r;
    }
    
    float getRadius()
    {
        return m_radius;
    }
    
    void updatePosition()
    {
		if(m_noRules)
		{
			m_v1.x = m_v2.x = m_v3.x = 0.0f;
			m_v1.y = m_v2.y = m_v3.y = 0.0f;
			m_position += (m_velocity) * velMult;
		}
		else
		{
			m_position += (m_v1 +m_v2);
		}
    }
    
	// for rule 1
	void setCenterAttraction(const Vec2f &_c)
	{
		m_v1 = _c;
	}

	void setOrientationAttractor(float _o)
	{
		m_oriAttr = _o;
	}

	// for rule 2
	void setSeparation(const Vec2f &_sep)
	{
		m_v2 = _sep;
	}

	Vec2f getSeparation()
	{
		return m_v2;
	}

    bool collision( Agent *otherAgent);
    bool collision( Map *map);
    bool collisionOptimized( Agent *otherAgent);
	bool contains(Vec2f mouse);

	void setNoRules(bool _b)
	{
		m_noRules = _b;
	}

	void setTargetBias(Vec2f &_b)
	{
		m_v3 = _b;
	}
	bool hasRules()
	{
		return !m_noRules;
	}

private:
    Vec2f m_position;
    Vec2f m_velocity;
    float m_radius;
	Vec2f m_dir;
   	// offset for rule 1 : push to barycenter
	Vec2f m_v1;
	// offset for rule 2 : separation
	Vec2f m_v2;
	// offset for rule 3 : target bias after collision
	Vec2f m_v3;
	float velMult;
protected:
	//
	bool m_noRules;
	//
	float m_oriAttr;
};



#endif /* defined(__Stephane__Agent__) */
