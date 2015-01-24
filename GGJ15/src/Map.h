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

enum cellState
{
	blocked = 1,
	unblocked,
	goal
};

class Map
{
public:
    Map(int width, int height):m_width(width),
                               m_height(height)
    {
        m_shader = gl::GlslProg (loadResource (BIRD_VERT), loadResource (BIRD_FRAG));
        m_grid = new int[width*height];
		m_cellWidth = getWindowWidth() / (float) m_width;
		m_cellHeight = getWindowHeight() / (float) m_height;
		console()<<m_cellWidth<<" "<<m_width<<" "<<getWindowWidth();
		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				m_grid[j*m_width + i] = cellState::unblocked;
			}
		}
    };
    
    void setState(int x, int y, int state)
    {
        m_grid[y*m_width+x] = state;
    }
    
    int getState(int x, int y)
    {
        return m_grid[y*m_width+x];
    }
	
	void addObstacle ()
	{
		
	}
    
    void draw()
    {
        gl::color( 1 , 0 , 1 );
        gl::setViewport( getWindowBounds() );
        gl::setMatricesWindow( getWindowSize() );

        gl::drawSolidRect( getWindowBounds() );
		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				if (m_grid[j*m_width + i] == cellState::blocked)
				{
					gl::color( 0 , 0 , 1 );
					gl::begin (GL_QUADS);
					gl::vertex (Vec2f ((i + 1) * m_cellWidth, (j + 1) * m_cellHeight));
					gl::vertex (Vec2f ((i + 1) * m_cellWidth, j * m_cellHeight));
					gl::vertex (Vec2f (i * m_cellWidth, j * m_cellHeight));
					gl::vertex (Vec2f (i * m_cellWidth, (j + 1) * m_cellHeight));
					gl::end();
				}
			}
		}
    }
private:
	int m_width, m_height;
	float m_cellWidth, m_cellHeight;
    int *m_grid;
    gl::GlslProg m_shader;
};

#endif /* defined(__Stephane__Map__) */
