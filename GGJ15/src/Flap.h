#pragma once

#ifndef __Flap__
#define __Flap__

#include "Bird.h"

#include <vector>

using namespace ci;

class Flap
{
public:
	//
	explicit Flap();
	//
	~Flap();
	//
	void update(std::vector<Bird*> &m_birds);
	//
	void removeAgents(int _num);
	//
	void rule1(std::vector<Bird*> &m_birds);
	//
	void rule2(std::vector<Bird*> &m_birds);
	// target following
	void rule3(std::vector<Bird*> &m_birds);
	//
	void setPosition(Vec2f _pos)
	{
		m_attractorPosition = _pos;
	}

	Vec2f getPosition()
	{
		return m_attractorPosition;
	}
	void setOrientation(float _o)
	{
		m_orientation = _o;
	}

	float getOrientation()
	{
		return m_orientation;
	}

	void orientation(std::vector<Bird*> &m_birds);

	Vec2f getVelocity()
	{
		return m_attractorVelocity;
	}

	void setVelocity(Vec2f _vel)
	{
		m_attractorVelocity = _vel;
	}
	
	void setVelocity(Vec2f _vel, std::vector<Bird*> &m_birds)
	{
		m_attractorVelocity = _vel;
		for( std::vector<Bird*>::iterator a = m_birds.begin(); a != m_birds.end(); ++a )
		{
			if ((*a)->hasRules())
			{
				(*a)->setVelocity (_vel);
			}
		}
	}
	
	bool contains( Vec2f p, float r){
		console()<<getPosition()<<" "<<p<<" "<<r<<std::endl;
		Vec2f posA = this->getPosition();
		Vec2f AB = posA - p;
		float lAB = AB.lengthSquared();
		
		return lAB < pow(r, 2.);
	}
	
	void setSpeed(float v)
	{
		velMult = v;
	}
	void updateOrientationForVelocity(Vec2f direction);

private:
	//
	float m_k_rule1;
	//
	float m_k_rule2;
	//
	float m_k_rule3;
	//
	Vec2f m_attractorPosition;
	//
	Vec2f m_attractorVelocity;
	//
	float m_orientation;
	//
	float m_k_attractor_strength;
	float velMult;


};

#endif