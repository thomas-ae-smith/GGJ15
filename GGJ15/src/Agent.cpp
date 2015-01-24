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

bool Agent::collision( Map *map){
    return true;
}