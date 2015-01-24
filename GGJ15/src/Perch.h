// Perch.h
// Added by Zack
// Class for the Perch that fires birds at the flock

#ifndef __GGJ15__Perch__
#define __GGJ15__Perch__

#include "Agent.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class Perch {
	public:

		Perch(Vec2f _pos, int _angle) 
		{
			pos = _pos;
			angle = _angle;
		}

	void setup() {

	}

	void update() {

	}

	void draw() {

	}
	
	Vec2f getPos() {
		return pos;
	}

	int getAngle() {
		return angle;
	}

	void setAngle(int _angle) {
		angle = _angle;
	}

	void setPos(Vec2f _pos) {
		pos = _pos;
	}

private:
	Vec2f pos;
	int angle;
	
};

#endif