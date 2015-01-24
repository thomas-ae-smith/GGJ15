//
//  Flap.h
//  Stephane
//
//  Created by Stephan LB on 24/01/2015.
//
//

#ifndef __Stephane__Flap__
#define __Stephane__Flap__

#include <stdio.h>
#include "Agent.h"

class Flap : public Agent
{
public:
    Flap(int posX, int posY):m_posX(posX), m_posY(posY){};
private:
    int m_posX, m_posY;
};

#endif /* defined(__Stephane__Flap__) */
