
#include "Flap.h"

Flap::Flap()
	: m_k_rule1(5)
	, m_k_rule2(40)
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
		            float F = (m_k_rule2/dist - 1.0f ) * 0.01f;
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
	m_attractorPosition += m_attractorVelocity;

	// apply barycenter rule (rule1)
	rule1(m_birds);
	// apply separation rule (rule2)
	rule2(m_birds);
	orientation(m_birds);

	// update positions
	for( std::vector<Bird*>::iterator a = m_birds.begin(); a != m_birds.end(); ++a )
	{
		(*a)->update();
	}
}

