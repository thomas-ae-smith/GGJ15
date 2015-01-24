#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
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
	void setupCamera();
	void setupLighting();
	void setupShaders();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	
	std::vector<Perch*> perches;
    std::vector<Bird*> birds;
    std::vector<Flap*> flaps;
    std::vector<Goal*> goals;
    
    Map *map;
	
	CameraPersp cam;
	Vec3f eye;
	
	Lighting* lighting;
	gl::GlslProg birdShader;
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

void GGJ15App::setupCamera()
{
	cam.setPerspective (60.0f, getWindowAspectRatio(), 5.0f, 3000.0f);
	eye        = Vec3f( 0.0f, 0.0f, 300.0f );
	Vec3f center     = Vec3f::zero();
	Vec3f up         = Vec3f::yAxis();
	cam.lookAt (eye, center, up);
	gl::setMatrices (cam);
}

void GGJ15App::setupLighting()
{
	lighting = new Lighting();
	lighting->setLPos (Vec3f (0., 0., 500.));
	lighting->setShininess (6.);
	lighting->setSpecular (Vec3f (1., 1., 1.));
	lighting->setDiffuse (Vec3f (0.6, 0.6, 0.6));
	lighting->setAmbient (Vec3f (0.3, 0.3, 0.3));
	lighting->setSpecularIntensity (1.);
	lighting->setDiffuseIntensity (0.2);
	lighting->setSpecularRadius (200.);
}

void GGJ15App::setupShaders()
{
	birdShader = gl::GlslProg (loadResource (BIRD_VERT), loadResource (BIRD_FRAG));
}

void GGJ15App::setup()
{
	setupCamera();
	setupLighting();
	setupShaders();
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
		birds.push_back(new Bird (Vec2f (xPos, yPos), Vec2f (5., 0.), 0., 20.));
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
	
	// Birds
	gl::enableAlphaBlending();
	gl::enableDepthRead( true );
	gl::enableDepthWrite( true );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	birdShader.bind();
	birdShader.uniform ("time" , (float) getElapsedSeconds());
	birdShader.uniform ("eyePos", Vec3f (0., 0., 300.));
	birdShader.uniform ("lPos", lighting->lPos);
	birdShader.uniform ("shininess", lighting->shininess);
	birdShader.uniform ("specular", lighting->specular);
	birdShader.uniform ("diffuse", lighting->diffuse);
	birdShader.uniform ("ambient", lighting->ambient);
	birdShader.uniform ("diffuseIntensity", lighting->diffuseIntensity);
	birdShader.uniform ("specularRadius", lighting->specularRadius);
	birdShader.uniform ("specularIntensity", lighting->specularIntensity);
    for (int i = 0; i < birds.size(); i++)
	{
		birds[i]->draw();
		birdShader.uniform ("normedBirdPosition", birds[i]->getNormedPosition());
		birdShader.uniform ("radius", Vec2f (birds[i]->getRadius() / getWindowWidth(), birds[i]->getRadius() / getWindowHeight()) * 2. - Vec2f (1.f, 1.f));
	}
	birdShader.unbind();
    //
}

CINDER_APP_NATIVE( GGJ15App, RendererGl )
