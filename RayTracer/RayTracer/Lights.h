/*
 *  PointLight.h
 *  RayTracer
 *
 */

#ifndef lights_h
#define lights_h

#include <Eigen/Dense>

enum typeOfLight {
	pointLight,
	directionalLight,
	abstractLight
};

class Light {
public:
	Eigen::Vector3f rgb;

	virtual Eigen::Vector4f getXYZ() const { return Eigen::Vector4f( 0.0f, 0.0f, 0.0f, 0.0f ); }
	virtual typeOfLight type() const { return abstractLight; }
	
};


class PointLight: public Light {
public:
	Eigen::Vector4f point;
	
	PointLight( float, float, float, float, float, float );
	Eigen::Vector4f getXYZ() const { return point; }
	typeOfLight type() const { return pointLight; }
};


class DirectionalLight: public Light {
public:
	Eigen::Vector4f direction;
	
	DirectionalLight( float, float, float, float, float, float );
	DirectionalLight( float, float, float, float rgb[3] );
	Eigen::Vector4f getXYZ() const { return direction; }
	typeOfLight type() const { return directionalLight; }
};

#endif