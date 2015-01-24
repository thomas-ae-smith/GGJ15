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
            m_radius(0.){}
    
    Agent(Vec2f position, float radius):m_position(position),
                                        m_velocity(Vec2f(0.,0.)),
                                        m_radius(radius){}
    
    Agent(Vec2f position, Vec2f velocity, float radius):m_position(position),
                                        m_velocity(velocity),
                                        m_radius(radius){}
    
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
        m_position += m_velocity;
    }
    
    bool collision( Agent *otherAgent);
    bool collision( Map *map);
private:
    Vec2f m_position;
    Vec2f m_velocity;
    float m_radius;
    
};



#endif /* defined(__Stephane__Agent__) */
