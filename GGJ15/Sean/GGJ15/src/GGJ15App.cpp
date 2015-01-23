#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GGJ15App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void GGJ15App::setup()
{
}

void GGJ15App::mouseDown( MouseEvent event )
{
}

void GGJ15App::update()
{
}

void GGJ15App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( GGJ15App, RendererGl )
