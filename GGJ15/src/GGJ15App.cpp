#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <vector>
#include "Bird.h"
#include "Perch.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GGJ15App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	
	std::vector<Perch*> perches;
    std::vector<Bird*> birds;
};

void GGJ15App::setup()
{
    // Parsing the file
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
		birds[i]->setPosition ((float) getMousePos().x, 200.);
	}
}

void GGJ15App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	for (int i = 0; i < birds.size(); i++)
	{
		birds[i]->draw();
	}
}

CINDER_APP_NATIVE( GGJ15App, RendererGl )
