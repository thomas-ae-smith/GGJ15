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

	std::vector<Perch*> perches;
    std::vector<Bird*> birds;
    std::vector<Flap*> flaps;
    std::vector<Goal*> goals;
    std::list<Bird*> clickedbirds;

	Flap *_flap;
    Map *map;
	gl::GlslProg birdShader;
	bool m_firstClicked;
};

GGJ15App::~GGJ15App()
{
	delete _flap;

    for(int i=0; i<perches.size() ; ++i)
    {
        delete perches[i];
    }
    
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
	m_firstClicked = true;
	_flap = new Flap();

	setWindowSize (800, 800);
	setupShaders();
    // Parsing the file
    std::ifstream setupFile("../../../resources/london.ggj");
    std::string line;
	
    bool initMap = true;
    bool initBirds, initFlaps, initGoal, initCard;
    initBirds = initFlaps = initGoal = initCard = false;
    int w,h;
    
    map = new Map(20,20);
	
	if (!setupFile.is_open())
	{
		console()<<"Couldn't open ../../../resources/london.ggj"<<endl;
	}
    while( std::getline( setupFile, line ) )
    {
        if(line.size() == 0 || line.at(0) == '#')
            continue;
        
        if(initMap)
        {
            std::sscanf(line.c_str(), "%d %d", w, h);
            map = new Map(w,h);
            initMap = false;
            initBirds =true;
            continue;
        }
        if(initBirds)
        {
            int n;
            std::sscanf(line.c_str(), "%d", n);
            birds.resize(n);
            for(int i = 0; i<n; i++)
            {
                std::getline( setupFile, line );
                if(line.size() == 0 || line.at(0) == '#')
                    continue;
                
                int positionX, positionY, angle;
                float velocityX, velocityY;
                
                std::sscanf(line.c_str(), "%d %d %f %f %d", positionX, positionY, velocityX, velocityY, angle);
                birds[i] = new Bird( Vec2f(positionX, positionY), Vec2f(velocityX, velocityY), 1., angle);
            }
            initBirds = false;
            initFlaps = true;
            continue;
        }
        if(initFlaps)
        {
            int n;
            std::sscanf(line.c_str(), "%d", n);
            flaps.resize(n);
            for(int i = 0; i<n; i++)
            {
                std::getline( setupFile, line );
                if(line.size() == 0 || line.at(0) == '#')
                    continue;
                
                int positionX, positionY;
                std::sscanf(line.c_str(), "%d %d", positionX, positionY);
                //flaps[i] = new Flap( positionX, positionY);
            }
            initFlaps = false;
            initGoal = true;
            continue;
        }
        if(initGoal)
        {
            int n;
            std::sscanf(line.c_str(), "%d", n);
            goals.resize(n);
            for(int i = 0; i<n; i++)
            {
                std::getline( setupFile, line );
                if(line.size() == 0 || line.at(0) == '#')
                    continue;
                
                int positionX, positionY;
                std::sscanf(line.c_str(), "%d %d", positionX, positionY);
                goals[i] = new Goal( positionX, positionY);
            }
            initGoal = false;
            initCard = true;
            continue;
        }
        if(initCard)
        {
            for(int i=0; i < h; i++, std::getline( setupFile, line ))
                for(int j=0; j < w; j++)
                {
                        map->setState(i, j, std::atoi(&(line.c_str()[j])));
                }
        }
        
        
    }
  
    
	//birds.push_back(new Bird (Vec2f (20, getWindowSize().y/2. ), Vec2f (1., 0.), 90, 20.));
	birds.push_back(new Bird (Vec2f (20, getWindowSize().y/2. ), Vec2f (1., 0.), 90, 25.));
	birds.push_back(new Bird (Vec2f (getWindowSize().x / 2.0, 0.0 ), Vec2f (0., 1.0), -90, 25.));
	birds.push_back(new Bird (Vec2f (getWindowSize().x -20, getWindowSize().y -120 ), Vec2f (-1., 0.0), -90, 25.));

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

void GGJ15App::update()
{
    // once collision, remove from list of clicked and set rules back
	// for every clicked bird, check if it is colliding with the any other bird of the flock
	bool collision = false;
	for( std::list<Bird*>::iterator a = clickedbirds.begin(); a != clickedbirds.end();a++)
	{
	    for(int i=0; i< birds.size(); i++)
		{
			 if( (*a != birds[i] ) && (*a)->collisionOptimized(birds[i]) )
			 {
				 birds[i]->setColor(0.0,0.0,1.0);
				// if they collide, remove from list and set norules
				 Vec2f newDirection = (_flap->getVelocity() + (*a)->getVelocity()).normalized();
				 _flap->setVelocity(newDirection);
				 (*a)->setNoRules(false);	// respond to rules as being now part of the flock
				 float ori = _flap->getOrientation() + (*a)->getOrientation();
				 if( ori < 0.0)
					 ori *=-1.0;
				 _flap->setOrientation(ori / 2.0);

				 a = clickedbirds.erase(a);
				 collision = true;
				 break;
			 }
		}
		if(collision)
			break;
	}

	// this applies the rules and updates attractor
	_flap->update(birds);

}

void GGJ15App::draw()
{
//    gl::enableAlphaBlending();
//    gl::enableDepthRead( true );
//    gl::enableDepthWrite( true );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    map->draw();
	
	// Birds
	birdShader.bind();
	birdShader.uniform ("time" , (float) getElapsedSeconds());
    for (int i = 0; i < birds.size(); i++)
	{
		birds[i]->draw();
	}
	birdShader.unbind();
}

CINDER_APP_NATIVE( GGJ15App, RendererGl )
