/*
 *  Sphere.h
 *  RayTracer
 *
 */
#ifndef sphere_h
#define sphere_h

#include <Eigen/Dense>
#include "Ray.h"

class Sphere {
public:
    float radius;
	Eigen::Vector4f center;
    float* ka;
    float* ks;
    float* kd;
    float sp;
	
    Sphere(float r, float x, float y, float z, float ambient[3], float specular[3], float diffuse[3], float sExponent);
	
	bool rayIntersectP( const Ray& ) const;
	float rayIntersect( const Ray& );
	
};

#endif