/*
 *  RayTracer.h
 *  RayTracer
 *
 */
#ifndef raytracer_h
#define raytracer_h

#include "Ray.h"
#include "Sphere.h"
#include <vector>

class RayTracer {
private:
	//const Sphere sphere;
	const std::vector< Sphere* > spheres;
	
public:
	
	RayTracer( const Sphere& );
	RayTracer( const std::vector< Sphere* >& );
	
	Ray generateRay( int, int, int, int );
	bool intersectionP( const Ray& );
	float intersection( const Ray&, Sphere* );

};

#endif