#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Resources.h"

#include <vector>
#include <list>
#include "Bird.h"
#include "Map.h"
#include "Flap.h"
#include "Goal.h"

#include <fstream>
#include <string>
#include <stdio.h>
#include "Perch.h"

#define NUM_LEVELS 4

using namespace ci;
using namespace ci::app;
using namespace std;

class GGJ15App : public AppNative {
  public:
    ~GGJ15App();
    
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void setupShaders();
	void addBirdAtGridPosition (int x, int y, float vX, float vY, float r);
	void addGoalAtPosition (int x, int y, float vX, float vY, float r);
	void setupLevel(int l);
	void keyDown( KeyEvent event );
	void setSpeed(float speed);
	
    std::vector<Bird*> birds;
    std::vector<Flap*> flaps;
    std::vector<Goal*> goals;
    std::list<Bird*> clickedbirds;
	Flap *_flap;
    Map *map;
	gl::GlslProg birdShader;
	bool m_firstClicked;
	int currentLevel;
	bool complete;
};

GGJ15App::~GGJ15App()
{
	delete _flap;
    
    for(int i=0; i<birds.size() ; ++i)
    {
        delete birds[i];
    }
    
    for(int i=0; i<flaps.size() ; ++i)
    {
        delete flaps[i];
    }
    
    for(int i=0; i<goals.size() ; ++i)
    {
        delete goals[i];
    }
    
    delete map;
}

void GGJ15App::setupShaders()
{
	#ifdef __APPLE__
		birdShader = gl::GlslProg (loadResource (BIRD_VERT), loadResource (BIRD_FRAG));
	#elif defined _WIN32 || defined _WIN64
		birdShader = gl::GlslProg (loadResource (BIRD_VERT,"GLSL"), loadResource (BIRD_FRAG,"GLSL"));
	#endif

}

void GGJ15App::setup()
{
	
	currentLevel = 0;
	complete = false;
	setWindowSize (800, 800);
	setupShaders();
	setupLevel(currentLevel);
	

}

void GGJ15App::setupLevel (int l)
{
	map = new Map(20,20);
	m_firstClicked = true;
	_flap = new Flap();
	clickedbirds.clear();
	birds.clear();
	
	switch (l)
	{
		case 0:
		{
			addBirdAtGridPosition (0, 9, 1., 0., 20.);
			map->setState (9, 9, cellState::goal);
			setSpeed (2.3f);
			break;
		}
		case 1:
		{
			addBirdAtGridPosition (3, 0, 0., 1., 20.);
			addBirdAtGridPosition (0, 14, 1., 0., 20.);
			map->setState (3, 14, cellState::target);
			map->setState (6, 17, cellState::goal);
			setSpeed (2.3f);
			break;
		}
		case 2:
		{
			addBirdAtGridPosition (3, 0, 0., 1., 20.);
			addBirdAtGridPosition (0, 10, 1., 0., 20.);
			map->setState (3, 10, cellState::target);
			addBirdAtGridPosition (8, 19, 0., -1., 20.);
			map->setState (8, 16, cellState::target);
			map->setState (16, 16, cellState::goal);
			setSpeed (2.3f);
			break;
		}
		case 3:
		{
			addBirdAtGridPosition (3, 0, 0., 1., 20.);
			addBirdAtGridPosition (0, 10, 1., 0., 20.);
			map->setState (3, 10, cellState::target);
			addBirdAtGridPosition (19, 5, -1., 1., 20.);
			map->setState (8, 16, cellState::target);
			map->setState (8, 17, cellState::goal);
			setSpeed (2.3f);
			break;
		}
        case 4:
        {
            std::string level = "20 21 5 11 19 0 -1 8 0 0 1 0 19 1 -1 14 0 -1 1 19 0 -1 1 1 1 11";
            std::stringstream sexStream(level);
            
            
            int w, h;
            sexStream >> w;
            sexStream >> h;
            this->map = new Map(w,h);
            
            int cardBirds;
            sexStream >> cardBirds;
            
            this->birds.resize(0);
            
            for( int i = 0 ; i< cardBirds ; ++i)
            {
                int posX, posY, velX, velY;
                sexStream >> posX;
                sexStream >> posY;
                sexStream >> velX;
                sexStream >> velY;
                
                this->addBirdAtGridPosition(posX, posY, velX, velY, 20);
            }
            
            
            int cardGoals;
            sexStream >> cardGoals;
            
            this->goals.resize(0);
            
            for( int i = 0 ; i< cardGoals ; ++i)
            {
                int posX, posY;
                sexStream >> posX;
                sexStream >> posY;
                
                map->setState(posX, posY, cellState::goal);
                // TODO
            }


            
        }
		default:
		{
			break;
		}
	}
	
	
	for (int i=0; i<birds.size(); i++)
	{
		birds[i]->setNoRules (true);
	}
}

void GGJ15App::setSpeed(float speed)
{
	for (int i = 0; i < birds.size(); i++)
	{
		birds[i]->setSpeedMultiplier (speed);
	}
	_flap->setSpeed (speed);
}

void GGJ15App::keyDown( KeyEvent event ) {
	if( event.getChar() == ' ' ){
		setupLevel(currentLevel);
	}
	else if ( event.getChar() == 's')
	{
		currentLevel++;
		setupLevel(currentLevel);
	}
//	else if( event.getChar() == 'h' ){
//		mRenderParticles = ! mRenderParticles;
//	}
}

void GGJ15App::addBirdAtGridPosition (int x, int y, float vX, float vY, float r)
{
	birds.push_back (new Bird (Vec2f ((x + 0.5) * r * 2., ((y + 0.5) * r * 2.)), Vec2f (vX, vY), r));
	map->addBirdAtPosition (birds[birds.size() - 1]->getPosition(), birds[birds.size() - 1]->getOrientation());
}

void GGJ15App::addGoalAtPosition (int x, int y, float vX, float vY, float r)
{
	//m_goal = new Goal(Vec2f ((x + 0.5) * r * 2., ((y + 0.5) * r * 2.)), Vec2f (vX, vY), r);
}

void GGJ15App::mouseDown( MouseEvent event )
{
    Vec2f pos = event.getPos();
    for(int i=0; i< birds.size(); i++)
        if(birds[i]->contains(pos))
        {
			if(m_firstClicked)	// initialize lastDir of the flock
			{
				m_firstClicked = false;
				_flap->setVelocity(birds[i]->getVelocity());
				_flap->setPosition(birds[i]->getPosition());
			}
            birds[i]->letsMove();
			birds[i]->setNoRules(true);
			if(!m_firstClicked)	// initialize lastDir of the flock
			{
				clickedbirds.push_back(birds[i]);
			}
        }
}

float clamp (float term, float lower, float higher)
{
	float ans = term;
	if (ans < lower) ans = lower;
	if (ans > higher) ans = higher;
	return ans;
}

void GGJ15App::update()
{
    // once collision, remove from list of clicked and set rules back
	// for every clicked bird, check if it is colliding with the any other bird of the flock
	bool collision = false;
	bool win = false;
	for( std::list<Bird*>::iterator a = clickedbirds.begin(); a != clickedbirds.end();a++)
	{
	    for(int i=0; i< birds.size(); i++)
		{
			 if( (*a != birds[i] ) && (*a)->collisionOptimized(birds[i],10) )
			 {
				// if they collide, remove from list and set norules
				 Vec2f flap_vel = _flap->getVelocity();
				 Vec2f newComer = (*a)->getVelocity();
				 Vec2f newDirection = (flap_vel + newComer); // normalize !
				 //newDirection.safeNormalize();
				 if (abs (newDirection.x) > 1.) newDirection.x /= 2.;
				 if (abs (newDirection.y) > 1.) newDirection.y /= 2.;
				 (*a)->setNoRules(false);	// now this bird becomes susbject to rules
				 _flap->setVelocity(newDirection, birds);
				 _flap->updateOrientationForVelocity (newDirection);
				 //_flap->setOrientation(ori);
				 a = clickedbirds.erase(a);
				 collision = true;
				 break;
			 }
		}
		if(collision)
			break;
	}
	for (int b = 0; b < birds.size(); b++)
	{
		map->setBirdPositionOrientation (birds[b]->getPosition(), birds[b]->getOrientation(), b);
		if (map->getNumTargets() > 0)
		{
			if (birds[b]->contains (map->getCurrentTargetPos()))
			{
				map->incrementTargetPos();
				break;
			}
		}
	}

	if ( _flap->contains (map->getGoalPosition(), map->getGoalRadius()) )
	{
		if (birds.size() > 1)
		{
			for (int i = 1; i < birds.size(); i++)
			{
				if (!birds[i]->hasRules())
				{
					break;
				}
				win = true;
			}
		}
		else
		{
			win = true;
		}
	}
	if (win)
	{
		
		currentLevel ++;
		if (currentLevel >= NUM_LEVELS)
		{
			complete = true;
		}
		else
		{
			setupLevel (currentLevel);
		}
	}
	else
	{
		// this applies the rules and updates attractor
		_flap->update(birds);
	}

}

void GGJ15App::draw()
{
//    gl::enableAlphaBlending();
//    gl::enableDepthRead( true );
//    gl::enableDepthWrite( true );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	if(!complete)
	{
		map->draw();
		
		// Birds
		//birdShader.bind();
		//birdShader.uniform ("time" , (float) getElapsedSeconds());
		for (int i = 0; i < birds.size(); i++)
		{
			birds[i]->draw();
		}
		//birdShader.unbind();
	}
	else
	{
		//completion screen
	}
}

CINDER_APP_NATIVE( GGJ15App, RendererGl )
