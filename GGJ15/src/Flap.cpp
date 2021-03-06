
#include "Flap.h"

Flap::Flap()
	: m_k_rule1(100)				// how much agents get attracted to center
	, m_k_rule2(30)					// separation distance
	, m_k_rule3(1.0)				// 
	, m_k_attractor_strength(0.03)	// force magnitude multiplier	
	, velMult (1.)
{
}

// clean up the mess
Flap::~Flap()
{
}


// RULE 1 : barycenter force
void Flap::rule1(std::vector<Bird*> &m_birds)
{
	for( std::vector<Bird*>::iterator a = m_birds.begin(); a != m_birds.end(); ++a )
	{
		//Vec2f perceivedCenter(com / (float)N_minus_one);	// this set the offset v1
		Vec2f v1 = (m_attractorPosition - (*a)->getPosition()) / m_k_rule1;
		//v1.safeNormalize();
		(*a)->setCenterAttraction(v1);
	}
}

// RULE 2 : separation
void Flap::rule2(std::vector<Bird*> &m_birds)
{
	Vec2f c;
	for( std::vector<Bird*>::iterator a = m_birds.begin(); a != m_birds.end(); ++a )
	{
		for( std::vector<Bird*>::iterator b = m_birds.begin(); b != m_birds.end(); ++b )
		{
			if(a!=b)	// not with itself
			{
				Vec2f dir = ((*a)->getPosition() -(*b)->getPosition());
				float dist = dir.length();

				if(dist < m_k_rule2)
				{
		            float F = (m_k_rule2/dist - 1.0f ) * m_k_attractor_strength;
					dir = dir.normalized() * F;

					(*a)->setSeparation((*a)->getSeparation() + dir);	// increase existing
					(*b)->setSeparation((*b)->getSeparation() - dir);	// decrease existing
				}
			}
		}
	}
}

// RULE 3 : target following
void Flap::rule3(std::vector<Bird*> &m_birds)
{
	for( std::vector<Bird*>::iterator b = m_birds.begin(); b != m_birds.end(); ++b )
	{
		Vec2f targetBias = (   ((*b)->getPosition() +3*m_attractorPosition) -(*b)->getPosition() ).normalized() / m_k_rule3;
		(*b)->setTargetBias(targetBias);
	}

}

void Flap::orientation(std::vector<Bird*> &m_birds)
{
	for( std::vector<Bird*>::iterator b = m_birds.begin(); b != m_birds.end(); ++b )
	{
		(*b)->setOrientationAttractor(m_orientation);
	}
}


// update all agents
// NOTE : dir has to be NORMALIZED (.normalized())
void Flap::update(std::vector<Bird*> &m_birds)
{
	m_attractorPosition += (m_attractorVelocity * velMult);

	// apply attraction rule (rule1)
	rule1(m_birds);
	// apply separation rule (rule2)
	rule2(m_birds);
	// orient boids
	orientation(m_birds);

	// update positions
	for( std::vector<Bird*>::iterator a = m_birds.begin(); a != m_birds.end(); ++a )
	{
		(*a)->update();
	}
}

void Flap::updateOrientationForVelocity (Vec2f direction)
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

