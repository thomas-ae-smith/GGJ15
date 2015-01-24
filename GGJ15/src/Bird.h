//
//  Bird.h
//  GGJ15
//
//  Created by Sean Soraghan on 23/01/2015.
//
//

#ifndef __GGJ15__Bird__
#define __GGJ15__Bird__

#include <stdio.h>
#include "Agent.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"
#include "Lighting.h"
using namespace ci;
using namespace ci::app;

class Bird : public Agent
{
public:
	Bird (Vec2f pos, Vec2f vel, float angle, float radius, Lighting& l)
	: Agent (pos, vel, radius),
	  orientation (angle),
	  light (l)
	{
		
		right = Vec3f (getRadius(), getRadius(), sin(getElapsedSeconds() * 20.) * getRadius());
		top = Vec3f (0., -getRadius(), 0.);
		centre = Vec3f (0., getRadius() / 2., 0.);
		
	}
	
	void calculateNormals()
	{
		Vec3f a = top - right;
		Vec3f b = centre - right;
		normalRight = cross (a, b);
		a = left - top;
		b = left - centre;
		normalLeft = -cross (a, b);
	}
	
	void update()
	{
		//position += velocity;
		left = Vec3f (-getRadius(), getRadius(), -sin(getElapsedSeconds() * 20.) * getRadius());
		right = Vec3f (getRadius(), getRadius(), sin(getElapsedSeconds() * 20.) * getRadius());
		calculateNormals();
	}
	
	void draw()
	{
		gl::enableAlphaBlending();
		gl::enableDepthRead( true );
		gl::enableDepthWrite( true );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		shader.bind();
		shader.uniform ("resolution", Vec2f ((float) getWindowWidth(), (float) getWindowHeight()));
		Vec2f normedPosition = getPosition() / Vec2f ((float) getWindowWidth(), (float) getWindowHeight()) * 2.f - Vec2f (1.f, 1.f);
		normedPosition.y *= -1.f;
		shader.uniform ("normedBirdPosition", normedPosition);
		shader.uniform ("radius", Vec2f (getRadius() / getWindowWidth(), getRadius() / getWindowHeight()) * 2. - Vec2f (1.f, 1.f));
		shader.uniform ("time" , (float) getElapsedSeconds());
		shader.uniform ("eyePos", Vec3f (0., 0., 300.));
		shader.uniform ("lPos", light.lPos);
		shader.uniform ("shininess", light.shininess);
		shader.uniform ("specular", light.specular);
		shader.uniform ("diffuse", light.diffuse);
		shader.uniform ("ambient", light.ambient);
		shader.uniform ("diffuseIntensity", light.diffuseIntensity);
		shader.uniform ("specularRadius", light.specularRadius);
		shader.uniform ("specularIntensity", light.specularIntensity);

		gl::pushMatrices();
		gl::color (1.0, 0., 0.);
		gl::translate (getPosition());
		gl::rotate (orientation);
		gl::begin (GL_TRIANGLE_STRIP);
		glNormal3f (normalRight);
		glVertex3f (right);
		glNormal3f (normalRight);
		gl::vertex (top);
		glNormal3f (normalRight);
		gl::vertex (centre);
		glNormal3f (normalLeft);
		gl::vertex (centre);
		glNormal3f (normalLeft);
		gl::vertex (top);
		glNormal3f (normalLeft);
		gl::vertex (left);
		gl::end();
		gl::rotate (-orientation);
		gl::translate (-getPosition());
		gl::popMatrices();
		shader.unbind();
	}
	
	void setOrientation (float o)
	{
		orientation = o;
	}
	float getOrientation()
	{
		return orientation;
	}
private:
	float orientation;
	
	Lighting& light;
	
	Vec3f right;
	Vec3f top;
	Vec3f centre;
	Vec3f left;
	Vec3f normalRight;
	Vec3f normalLeft;
	
	Vec3f cross (Vec3f a, Vec3f b)
	{
		return Vec3f (a.y * b.z - a.z * b.y,
					  a.z * b.x - a.x * b.z,
					  a.x * b.y - a.y * b.x);
	}
	
	Vec3f rotateZ (Vec3f p, float ang)
	{
		Matrix33<float> rot = Matrix33<float>(cos (ang), -sin (ang), 0.,
											  sin (ang), cos (ang), 0.,
											  0., 0., 1.);
		return rot * p;
	}
	
};

#endif /* defined(__GGJ15__Bird__) */
