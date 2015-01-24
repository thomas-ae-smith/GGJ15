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



};

#endif