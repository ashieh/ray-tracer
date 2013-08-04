/*
 *  Sphere.cpp
 *  RayTracer
 *
 */

#include <Eigen/Dense>
#include "Sphere.h"
using namespace std;
using namespace Eigen;

Sphere::Sphere (float r, float x, float y, float z, float ambient[3], float specular[3], float diffuse[3], float sExponent) {
	radius = r;
	center(0) = x;
	center(1) = y;
	center(2) = z;
	center(3) = 1.0f;
	ka = ambient;
	ks = specular;
	kd = diffuse;
	sp = sExponent;
}


bool Sphere::rayIntersectP( const Ray& ray) const {
	float val;
	float tempRadius = radius;
	Vector4f eMinusC = ray.e - center;
	float A = ray.d.dot( ray.d );
	float B = 2 * ray.d.dot( eMinusC );
	float C = eMinusC.dot( eMinusC ) - pow( tempRadius, 2 );
	
	val = pow(B, 2) - 4 * A * C;
	
	return val >= 0;
}

float Sphere::rayIntersect( const Ray& ray ) {
	float temp = radius;
	Vector4f eMinusC = ray.e - center;
	float A = ray.d.dot( ray.d );
	float C = eMinusC.dot( eMinusC ) - pow( temp, 2 );
	float squareRoot = sqrt( pow( ray.d.dot( eMinusC ), 2 ) - A * C );
	temp = -ray.d.dot( eMinusC );
	float t1 = temp + squareRoot;
	float t2 = temp - squareRoot;
	
	return min( t1, t2 );	
}