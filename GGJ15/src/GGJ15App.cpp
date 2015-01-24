#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Resources.h"

#include <vector>
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
	
	std::vector<Perch*> perches;
    std::vector<Bird*> birds;
    std::vector<Flap*> flaps;
    std::vector<Goal*> goals;
    
    Map *map;
};

GGJ15App::~GGJ15App()
{
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

void GGJ15App::setup()
{
    // Parsing the file
    std::ifstream setupFile;
    setupFile.open("london.ggj");
    
    std::string line;
    bool initMap = true;
    bool initBirds, initFlaps, initGoal, initCard;
    initBirds = initFlaps = initGoal = initCard = false;
    int w,h;
    
    map = new Map(50,50);
    
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
                flaps[i] = new Flap( positionX, positionY);
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
    
    
	birds.push_back(new Bird (Vec2f (100., 100.), Vec2f (5., 0.), 45., 90.));
	birds[0]->setPosition (Vec2f (300., 300.));
	birds[0]->setRadius (50.);

    birds.push_back(new Bird (Vec2f (300., 300.), Vec2f (5., 0.), 45., 90.));
	//Create perch points from the map
	//birds.push_back(new Perch
}

void GGJ15App::mouseDown( MouseEvent event )
{
	/* Test stuff at the moment, ignore */
	int xPos = event.getX();
	int yPos = event.getY();
	if (xPos >= 0 && xPos <= 100) {
		birds.push_back(new Bird (Vec2f (xPos, yPos), Vec2f (5., 0.), 0, 20));
	}
}

void GGJ15App::update()
{
    // Collision
	for (int i = 0; i < birds.size(); i++)
	{
		birds[i]->update();
		birds[i]->setPosition ((float) getMousePos().x, (float) getMousePos().y);
	}
}

void GGJ15App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    map->draw();
    
    for (int i = 0; i < birds.size(); i++)
	{
		birds[i]->draw();
	}
    
}

CINDER_APP_NATIVE( GGJ15App, RendererGl )
