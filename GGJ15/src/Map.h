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
	target,
	goal
};

class Map
{
public:
    Map(int width, int height):m_width(width),
                               m_height(height)
    {
		#ifdef __APPLE__
			m_shader = gl::GlslProg (loadResource (BIRD_VERT), loadResource (MAP_FRAG));
		#elif defined _WIN32 || defined _WIN64
			m_shader = gl::GlslProg (loadResource (BIRD_VERT,"GLSL"), loadResource (BIRD_FRAG,"GLSL"));
		#endif
        m_grid = new int[width*height];
		m_cellWidth = getWindowWidth() / (float) m_width;
		m_cellHeight = getWindowHeight() / (float) m_height;
		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				m_grid[j*m_width + i] = cellState::unblocked;
			}
		}
		//m_grid[9 * m_width + 13] = cellState::goal;
//		goalPosition = Vec2f(13., 9.);
		targetIndex = 0;
		numTargets = 0;
		goalRadius = 40.;
    };
    
    void setState(int x, int y, int state)
    {
        m_grid[y*m_width+x] = state;
		Vec2f windowPos = Vec2f ((x + 0.5) * m_cellWidth, (y + 0.5) * m_cellHeight);
		Vec2f normedPos = windowPos / Vec2f ((float) getWindowWidth(), (float) getWindowHeight()) * 2.f - Vec2f (1.f, 1.f);
		normedPos.y *= -1.f;
		if (state == cellState::target)
		{
			m_targetPositions.push_back (windowPos);
			
			m_normedTargetPositions.push_back (normedPos);

		}
		else if (state == cellState::goal)
		{
			goalPosition = windowPos;
			m_normedGoalPos = normedPos;
		}
    }
    
    int getState(int x, int y)
    {
        return m_grid[y*m_width+x];
    }
	
	void addObstacle (int x, int y, int radius)
	{
		for (int i = x; i < x + radius*2; x++)
		{
			for (int j = y; j < y + radius * 2; j++)
			{
				m_grid[j * m_width + i] = cellState::blocked;
			}
		}
	}
    
    void draw()
    {
        //gl::color( 1 , 0 , 1 );
        gl::setViewport( getWindowBounds() );
        gl::setMatricesWindow( getWindowSize() );
		m_shader.bind();
		m_shader.uniform ("outputColor",Vec3f(1.0, 1.0, 0.0));
		m_shader.uniform ("numTargets", (int)m_normedTargetPositions.size());
		if (m_normedTargetPositions.size() > 0)
		{
			m_shader.uniform ("normedTargetPosition", m_normedTargetPositions[targetIndex]);
		}
		m_shader.uniform ("normedGoalPosition", m_normedGoalPos);
		m_shader.uniform ("resolution", Vec2f ((float) getWindowWidth(), (float) getWindowHeight()));
		m_shader.uniform ("time", float(getElapsedSeconds()));
        gl::drawSolidRect( getWindowBounds() );
		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				if (m_grid[j*m_width + i] == cellState::blocked)
				{
					//gl::color( 0 , 0 , 1 );
					gl::begin (GL_QUADS);
					gl::vertex (Vec2f ((i + 1) * m_cellWidth, (j + 1) * m_cellHeight));
					gl::vertex (Vec2f ((i + 1) * m_cellWidth, j * m_cellHeight));
					gl::vertex (Vec2f (i * m_cellWidth, j * m_cellHeight));
					gl::vertex (Vec2f (i * m_cellWidth, (j + 1) * m_cellHeight));
					gl::end();
				}
			}
		}
		m_shader.unbind();
    }
	
	Vec2f getCurrentTargetPos()
	{
		return m_targetPositions[targetIndex];
	}
	void incrementTargetPos()
	{
		targetIndex ++;
		if (targetIndex > m_targetPositions.size())
		{
			targetIndex = 0;
		}
	}
	int getNumTargets()
	{
		return numTargets;
	}

	Vec2f getGoalPosition()
	{
		return goalPosition;
	}
	float getGoalRadius()
	{
		return goalRadius;
	}
private:
	int targetIndex;
	int m_width, m_height;
	float m_cellWidth, m_cellHeight;
    int *m_grid;
    gl::GlslProg m_shader;
	Vec2f goalPosition;
	Vec2f m_normedGoalPos;
	std::vector<Vec2f> m_normedTargetPositions;
	std::vector<Vec2f> m_targetPositions;
	int numTargets;
	float goalRadius;
};

#endif /* defined(__Stephane__Map__) */
