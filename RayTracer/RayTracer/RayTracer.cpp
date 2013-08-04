/*
 *  RayTracer.cpp
 *  RayTracer
 *
 */
#include <Eigen/Dense>
#include "RayTracer.h"
#include "Ray.h"
#include "Sphere.h"

using namespace std;
using namespace Eigen;

RayTracer::RayTracer( const vector< Sphere* >& spheresList )
: spheres( spheresList )
{}
	

Ray RayTracer::generateRay( int i, int j, int frameX, int frameY ) {
	
	float u = -1.0f + 2 * ((float) i + 0.5f ) / frameX;
	float v = -1.0f + 2 * ((float) j + 0.5f ) / frameY;
	
	Ray outputRay(Vector4f( 0.0f, 0.0f,  0.0f, 1.0f ), Vector4f(    u,    v, -1.0f, 0.0f ) ) ;
	return outputRay;
}

bool RayTracer::intersectionP( const Ray& r ) {
	for ( vector< int >::size_type x = 0; x < spheres.size(); ++x ) {
		if ( spheres[x]->rayIntersectP( r ) )
			return true;
	}
	return false;
}

float RayTracer::intersection( const Ray& r, Sphere* intersectedObject ) {
	float temp = 0.0f;
	vector< int >::size_type x = 0;
	float t = spheres[x]->rayIntersect( r );
	x++;
	for ( ; x < spheres.size(); ++x ) {
		temp = spheres[x]->rayIntersect( r );
		if ( temp < t ) {
			t = temp;
			intersectedObject = spheres[x];
		}
	}
	return t;
			
	
}


