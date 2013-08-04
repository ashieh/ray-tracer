/*
 *  Ray.h
 *  RayTracer
 *
 */
#ifndef ray_h
#define ray_h
#include <Eigen/Dense>
#include <Eigen/StdVector>



/*
 * Represents the e + dt Ray
 */
class Ray {
	
public:
	Eigen::Vector4f e;		//end
	Eigen::Vector4f d;		//destination
	
	Ray( Eigen::Vector4f& start, Eigen::Vector4f& end ){
	e=start;
	d=end;
	}
		
};

#endif