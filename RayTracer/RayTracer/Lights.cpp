/*
 *  PointLight.cpp
 *  RayTracer
 *
 *  Created by James Turley on 10/1/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Lights.h"
#include <Eigen/Dense>

PointLight::PointLight( float x, float y, float z, float red, float green, float blue ) {
	point(0) = x;
	point(1) = y;
	point(2) = z;
	point(3) = 1.0f;
	rgb(0) = red;
	rgb(1) = green;
	rgb(2) = blue;
}

DirectionalLight::DirectionalLight( float x, float y, float z, float red, float green, float blue ) {
	direction(0) = x;
	direction(1) = y;
	direction(2) = z;
	direction(3) = 1.0f;
	rgb(0) = red;
	rgb(1) = green;
	rgb(2) = blue;
}

DirectionalLight::DirectionalLight( float x, float y, float z, float paramRGB[3] ) {
	direction(0) = x;
	direction(1) = y;
	direction(2) = z;
	direction(3) = 1.0f;
	rgb(0) = paramRGB[0];
	rgb(1) = paramRGB[1];
	rgb(2) = paramRGB[2];
}