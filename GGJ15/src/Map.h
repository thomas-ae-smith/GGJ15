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
		#ifdef __APPLE__
			m_shader = gl::GlslProg (loadResource (BIRD_VERT), loadResource (BIRD_FRAG));
		#elif defined _WIN32 || defined _WIN64
			m_shader = gl::GlslProg (loadResource (BIRD_VERT,"GLSL"), loadResource (BIRD_FRAG,"GLSL"));
		#endif
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
        gl::clear( Color(255,255,255));
        gl::color(1., 0., 0.);
        gl::begin(GL_QUADS);
            gl::vertex(1, 1);
            gl::vertex(1, -1);
            gl::vertex(-1,-1);
            gl::vertex(-1, 1);
        gl::end();
    }
private:
    int m_width, m_height;
    int *m_grid;
    gl::GlslProg m_shader;
};

#endif /* defined(__Stephane__Map__) */
