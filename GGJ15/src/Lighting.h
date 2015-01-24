//
//  Lighting.h
//  GGJ15
//
//  Created by Sean Soraghan on 24/01/2015.
//
//
#include <stdio.h>
#include "Agent.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "Resources.h"

#ifndef GGJ15_Lighting_h
#define GGJ15_Lighting_h

class Lighting
{
public:
	Lighting()
	{
		
	}
	void setLPos (Vec3f p) {lPos = p;}
	void setShininess (float s) {shininess = s;}
	void setSpecular (Vec3f s) {specular = s;}
	void setDiffuse (Vec3f d) {diffuse = d;}
	void setAmbient (Vec3f a) {ambient = a;}
	void setSpecularIntensity (float s) {specularIntensity = s;}
	void setDiffuseIntensity (float d) {diffuseIntensity = d;}
	void setSpecularRadius (float r) {specularRadius = r;}
	
	Vec3f lPos;
	float shininess;
	Vec3f specular;
	Vec3f diffuse;
	Vec3f ambient;
	
	float diffuseIntensity;
	float specularRadius;
	float specularIntensity;
};

#endif
