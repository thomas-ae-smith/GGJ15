
#include "Flap.h"

Flap::Flap()
	: m_k_rule1(100)
	,m_k_rule2(20*20)
	, m_k_rule3(1.0)
{
}

// clean up the mess
Flap::~Flap()
{
}


// RULE 1 : barycenter force
void Flap::rule1(std::vector<Bird*> &m_birds)
{
	/*
	Vec2f com;
	int N_minus_one = m_birds.size()-1;
	// update "perceived" centre of mass	

		com.zero();
		for( std::vector<Bird*>::iterator b = m_birds.begin(); b != m_birds.end(); ++b )
		{
			if(a!=b)	// not with itself
			{
				com += (*b)->getPosition();	// barycenter excluding itself
			}
		}
*/
	for( std::vector<Bird*>::iterator a = m_birds.begin(); a != m_birds.end(); ++a )
	{
		//Vec2f perceivedCenter(com / (float)N_minus_one);	// this set the offset v1
		Vec2f v1 = (m_attractorPosition - (*a)->getPosition()) / m_k_rule1;
		(*a)->setCenterAttraction(v1);
	}
}

// RULE 2 : separation
void Flap::rule2(std::vector<Bird*> &m_birds)
{
	/*
	Vec2f v2;
	for( std::vector<Bird*>::iterator a = m_birds.begin(); a != m_birds.end(); ++a )
	{
		for( std::vector<Bird*>::iterator b = m_birds.begin(); b != m_birds.end(); ++b )
		{
			if(a!=b)	// not with itself
			{
				Vec2f posA = (*a)->getPosition();
				Vec2f posB = (*b)->getPosition();
				Vec2f dirAB = posA - posB;
				float distSquared = dirAB.lengthSquared(); // no need for expensive square root
				float zoneRadius = ((*a)->getRadius() + (*b)->getRadius());
				m_k_rule2 = zoneRadius*zoneRadius;
				float dist = distSquared - m_k_rule2;
				if(dist < 0)
				{
					float magnitude = (m_k_rule2/distSquared - 1.0f) * 0.01f;
					v2 = v2.normalized() * magnitude;
					(*a)->setSeparation((*a)->getSeparation() + v2);	// increase existing
					(*b)->setSeparation((*b)->getSeparation() - v2);	// decrease existing
				}
			}
		}
	}
	*/

	Vec2f c;
	for( std::vector<Bird*>::iterator a = m_birds.begin(); a != m_birds.end(); ++a )
	{
		for( std::vector<Bird*>::iterator b = m_birds.begin(); b != m_birds.end(); ++b )
		{
			if(a!=b)	// not with itself
			{
				Vec2f dir = ((*a)->getPosition() -(*b)->getPosition());
				float dist = dir.length();

				if(dist < 40)
				{
		            float F = (40/dist - 1.0f ) * 0.03f;
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
/*	for( std::vector<Bird*>::iterator b = m_birds.begin(); b != m_birds.end(); ++b )
	{
		Vec2f targetBias = (   ((*b)->getPosition() +3*m_target) -(*b)->getPosition() ).normalized() / m_k_rule3;
		(*b)->setTargetBias(targetBias);
	}
*/
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
	m_attractorPosition += m_attractorVelocity;

	// apply barycenter rule (rule1)
	rule1(m_birds);
	// apply separation rule (rule2)
	rule2(m_birds);
	orientation(m_birds);
	// make follow he target direction after collision
	//rule3(m_birds);

	// update positions
	for( std::vector<Bird*>::iterator a = m_birds.begin(); a != m_birds.end(); ++a )
	{
		(*a)->update();
	}
}

void Flap::updateOrientationForVelocity (Vec2f direction)
{
	if (direction.x == 0 && direction.y == 1)
	{
		m_orientation = 0.;
	}
	else if (direction.x == 1 && direction.y == 1)
	{
		m_orientation = 45.;
	}
	else if (direction.x == 1 && direction.y == 0)
	{
		m_orientation = 90.;
	}
	else if (direction.x == 1 && direction.y == -1)
	{
		m_orientation = 125.;
	}
	else if (direction.x == 0 && direction.y == -1)
	{
		m_orientation = 180.;
	}
	else if (direction.x == -1 && direction.y == 1)
	{
		m_orientation = 225.;
	}
	else if (direction.x == -1 && direction.y == 0)
	{
		m_orientation = 270.;
	}
	else if (direction.x == -1 && direction.y == -1)
	{
		m_orientation = 315.;
	}
}

