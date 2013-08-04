/*
 *  PhongIllumination.cpp
 *  RayTracer
 */

#include "PhongIllumination.h"
#include <Eigen/Dense>
#include <vector>

using namespace std;
using namespace Eigen;

Vector3f sphereShading( int i, int j,
					    const Sphere* sphere, 
						const std::vector< Light* >& lightsList ) {
	
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	float* ambient;
	float* diffuse;
	float* specular;
	
	//cout << lightsList[0]->rgb << endl;
	//cout << lightsList[0]->getXYZ() << endl;
	
	float z = sqrt((float)(sphere->radius*sphere->radius) - ((float)(i*i) + (float)(j*j)));
	
	float normalLength = sqrt((z*z) + (i*i) + (j*j));
	float normal[3];
	normal[0] = j/normalLength;
	normal[1] = i/normalLength;
	normal[2] = z/normalLength;
	
	
	for ( vector< int >::size_type x = 0; x < lightsList.size(); ++x ) {
		
		diffuse = getDiffuse(j, i, z, sphere->radius, normal, lightsList[x], sphere);
		ambient = getAmbient( sphere, lightsList[x] );
		specular = getSpecular(j, i, z, sphere->radius, normal, lightsList[x], sphere);
		
		red += diffuse[0] + ambient[0] + specular[0];
		green += diffuse[1] + ambient[1] + specular[1];
		blue += diffuse[2] + ambient[2] + specular[2];
	}
	
	return Vector3f( red, green, blue );
}


static float* getAmbient( const Sphere* sphere, const Light* light ) {
	
	float* ambientRGB = new float[3];
	ambientRGB[0] = sphere->ka[0] * light->rgb[0];
	ambientRGB[1] = sphere->ka[1] * light->rgb[1];
	ambientRGB[2] = sphere->ka[2] * light->rgb[2];
	return ambientRGB;
}


//modified version
static float* getDiffuse( int x, int y, int z, int radius,
						  const float (&normal)[3],
						  const Light* light,
						  const Sphere* sphere ) {
	
	Vector4f temp4f = light->getXYZ();
	cout << light->rgb[0] << endl;
	cout << light->rgb[1] << endl;
	cout << light->rgb[2] << endl;
	float argVector[6] = { temp4f(0), temp4f(1), temp4f(2), light->rgb[0], light->rgb[1], light->rgb[2] };
	float* diffuseRGB = new float[3];
	
	float tempVec[3];
	if (light->type() == directionalLight) {
		tempVec[0] = -radius * argVector[0];
		tempVec[1] = -radius * argVector[1];
		tempVec[2] = -radius * argVector[2];
	} else {	
		tempVec[0] = radius * argVector[0] - x;
		tempVec[1] = radius * argVector[1] - y;
		tempVec[2] = radius * argVector[2] - z;
	}
	
	float lightLength = sqrt((tempVec[0]*tempVec[0]) + (tempVec[1]*tempVec[1]) + (tempVec[2]*tempVec[2]));
	float vecLight[3];
	vecLight[0] = tempVec[0] / lightLength;
	vecLight[1] = tempVec[1] / lightLength;
	vecLight[2] = tempVec[2] / lightLength;
	
	//vecLight (dot) normal
	float temp = (normal[0] * vecLight[0]) + (normal[1] * vecLight[1]) + (normal[2] * vecLight[2]);
	tempVec[0] = max(sphere->kd[0] * argVector[3] * temp, 0.0f);
	tempVec[1] = max(sphere->kd[1] * argVector[4] * temp, 0.0f);
	tempVec[2] = max(sphere->kd[2] * argVector[5] * temp, 0.0f);
	
	diffuseRGB[0] = tempVec[0];
	diffuseRGB[1] = tempVec[1];
	diffuseRGB[2] = tempVec[2];
	
	return diffuseRGB;
	
}

//modified version
static float* getSpecular( int x, int y, int z, int radius,
						   const float (&normal)[3],
						   const Light* light,
						   const Sphere* sphere ) {
	
	Vector4f temp = light->getXYZ();
	float argVector[6] = { temp(0), temp(1), temp(2), light->rgb[0], light->rgb[1], light->rgb[2] };
	
	float* specularRGB = new float[3];
	float* lightV = new float[3];
	if (light->type() == directionalLight) {
		lightV[0]=-argVector[0]*radius;
		lightV[1]=-argVector[1]*radius;
		lightV[2]=-argVector[2]*radius;
	} else { //point light
		lightV[0] = argVector[0]*radius-x;
		lightV[1] = argVector[1]*radius-y;
		lightV[2] = argVector[2]*radius-z;
	}
	float lightVLength = sqrt((float)lightV[0]*lightV[0]+lightV[1]*lightV[1]+lightV[2]*lightV[2]);
	lightV[0] = lightV[0]/lightVLength;
	lightV[1] = lightV[1]/lightVLength;
	lightV[2] = lightV[2]/lightVLength;
	float* reflectVector;
	reflectVector = getReflect(normal, lightV);
	float viewerV[] = {0.0f, 0.0f, 1.0f};
	float rDotV = reflectVector[0]*viewerV[0]+reflectVector[1]*viewerV[1]+reflectVector[2]*viewerV[2];
	float specterm = max(rDotV, 0.0f);
	specterm = pow(specterm, (int) sphere->sp);
	specularRGB[0] = sphere->ks[0]*argVector[3]*specterm;
	specularRGB[1] = sphere->ks[1]*argVector[4]*specterm;
	specularRGB[2] = sphere->ks[2]*argVector[5]*specterm;
	return specularRGB;
	
}

static float* getReflect(const float (&normal)[3], float light[]){
    float* reflectance = new float[3];
    float negLX = -light[0];
    float negLY = -light[1];
    float negLZ = -light[2];
    float dotProduct = normal[0]*light[0]+normal[1]*light[1]+normal[2]*light[2];
    reflectance[0] = negLX + 2*dotProduct * normal[0];
    reflectance[1] = negLY + 2*dotProduct * normal[1];
    reflectance[2] = negLZ + 2*dotProduct * normal[2];
    return reflectance;
	
}