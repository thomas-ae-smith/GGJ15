//
//  Map.h
//  Stephane
//
//  Created by Stephan LB on 24/01/2015.
//
//

#ifndef __Stephane__Map__
#define __Stephane__Map__

#include <stdio.h>
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

class Map
{
public:
    Map(int width, int height):m_width(width),
                               m_height(height)
    {
        grid = new int[width*height];
    };
    
    void setState(int x, int y, int state)
    {
        grid[y*m_width+x] = state;
    }
    
    int getState(int x, int y)
    {
        return grid[y*m_width+x];
    }
private:
    int m_width, m_height;
    int *grid;
};

#endif /* defined(__Stephane__Map__) */
