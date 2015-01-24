#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Bird.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GGJ15App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	
	Bird* birds[1];
};

void GGJ15App::setup()
{
	birds[0] = new Bird (Vec2f (100., 100.), Vec2f (5., 0.), 0., 10.);
}

void GGJ15App::mouseDown( MouseEvent event )
{
}

void GGJ15App::update()
{
	for (int i = 0; i < 1; i++)
	{
		birds[0]->update();
	}
}

void GGJ15App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	for (int i = 0; i < 1; i++)
	{
		birds[0]->draw();
	}
}

CINDER_APP_NATIVE( GGJ15App, RendererGl )
