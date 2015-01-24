//
//  Map.h
//  Stephane
//
//  Created by Stephan LB on 24/01/2015.
//
//

#ifndef __Stephane__Map__
#define __Stephane__Map__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"

#include "Resources.h"

#include <stdio.h>

using namespace ci;
using namespace ci::app;

class Map
{
public:
    Map(int width, int height):m_width(width),
                               m_height(height)
    {
        m_shader = gl::GlslProg (loadResource (BIRD_VERT), loadResource (BIRD_FRAG));
        m_grid = new int[width*height];
    };
    
    void setState(int x, int y, int state)
    {
        m_grid[y*m_width+x] = state;
    }
    
    int getState(int x, int y)
    {
        return m_grid[y*m_width+x];
    }
    
    void draw()
    {
        gl::color( 1 , 0 , 1 );
        gl::setViewport( getWindowBounds() );
        gl::setMatricesWindow( getWindowSize() );

        gl::drawSolidRect( getWindowBounds() );
    }
private:
    int m_width, m_height;
    int *m_grid;
    gl::GlslProg m_shader;
};

#endif /* defined(__Stephane__Map__) */
