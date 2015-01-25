//
//  Agent.cpp
//  Stephane
//
//  Created by Stephan LB on 23/01/2015.
//
//

#include "Agent.h"

bool Agent::collision( Agent *otherAgent){
    Vec2f posA = this->getPosition();
    Vec2f posB = otherAgent->getPosition();
    Vec2f AB = posA - posB;
    float lAB = AB.length();
    float dist = lAB - this->getRadius() - otherAgent->getRadius();
    return dist <= 0;
}

bool Agent::contains( Vec2f mouse){
    Vec2f posA = this->getPosition();
    Vec2f AB = posA - mouse;
    float lAB = AB.lengthSquared();
    
    return lAB < pow(this->getRadius() * 2.,2.);
}

bool Agent::collisionOptimized( Agent *otherAgent){
    Vec2f posA = this->getPosition();
    Vec2f posB = otherAgent->getPosition();
    Vec2f AB = posA - posB;
    float lAB = AB.lengthSquared();	// no need for expensive square root
	float zoneRadius = (this->getRadius() + otherAgent->getRadius());
    float dist = lAB - (zoneRadius*zoneRadius);
    return dist <= 0;
}

bool Agent::collision( Map *map){
    return true;
}