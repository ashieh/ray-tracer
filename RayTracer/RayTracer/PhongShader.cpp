/*
 *  PhongShader.cpp
 *  RayTracer
 *
 *  Created by James Turley on 9/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <Eigen/Dense>
#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

using namespace Eigen;
using namespace std;

#define PI 3.14159265







//****************************************************
// Some Classes
//****************************************************

class Viewport;

class Viewport {
public:
	int w, h; // width and height
};


//****************************************************
// Global Variables
//****************************************************
Viewport	viewport;
int 		plotX = 0;
int 		plotY = 0;
float ka[] = {0.0f, 0.0f, 0.0f};
float ks[] = {0.0f, 0.0f, 0.0f};
float kd[] = {0.0f, 0.0f, 0.0f};
float p1[6] = {3.0f, 5.0f, 1.0f, 0.7f, 0.7f, 0.5f};
float p2[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float p3[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float p4[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float p5[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float d1[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float d2[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float d3[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float d4[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float d5[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float specPowerCoefficient = 1.0f;
int numPL = 0;
int numDL = 0;

void initScene(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent
	
	glViewport (0,0,viewport.w,viewport.h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,viewport.w, 0, viewport.h);
}


//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
	viewport.w = w;
	viewport.h = h;
	
	glViewport (0,0,viewport.w,viewport.h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, viewport.w, 0, viewport.h);
	
}

void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
	glColor3f(r, g, b);
	glVertex2f(x+0.5, y+0.5);
}

//Color diffuseTerm(double light[], int x, int y, int z){


void circle(int x, int y, int radius) {
	
	float red;
	float green;
	float blue;
	float* ambient;
	float* diffuse;
	float* specular;
	
	// Draw inner circle
	glBegin(GL_POINTS);
	
	for (int i = -radius; i <= radius; i++) {
		int width = (int)(sqrt((float)(radius*radius-i*i)) + 0.5f);
		for (int j = -width; j <= width; j++) {
			
			red = 0.0f;
			green = 0.0f;
			blue = 0.0f;
			
			if ((float)(i*i) + (float)(j*j) > (float)(radius*radius))
				continue;
			float z = sqrt((float)(radius*radius) - ((float)(i*i) + (float)(j*j)));
			
			float normalLength = sqrt((z*z) + (i*i) + (j*j));
			float normal[3];
			normal[0] = j/normalLength;
			normal[1] = i/normalLength;
			normal[2] = z/normalLength;
			
			switch (numPL) {
				case 5:
					diffuse = getDiffuse(j, i, z, radius, normal, p5, pointLight);
					ambient = getAmbient(p5);
					specular = getSpecular(j, i, z, radius, normal, p5, pointLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
				case 4:
					diffuse = getDiffuse(j, i, z, radius, normal, p4, pointLight);
					ambient = getAmbient(p4);
					specular = getSpecular(j, i, z, radius, normal, p4, pointLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
				case 3:
					diffuse = getDiffuse(j, i, z, radius, normal, p3, pointLight);
					ambient = getAmbient(p3);
					specular = getSpecular(j, i, z, radius, normal, p3, pointLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
				case 2:
					diffuse = getDiffuse(j, i, z, radius, normal, p2, pointLight);
					ambient = getAmbient(p2);
					specular = getSpecular(j, i, z, radius, normal, p2, pointLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
				case 1:
					diffuse = getDiffuse(j, i, z, radius, normal, p1, pointLight);
					ambient = getAmbient(p1);
					specular = getSpecular(j, i, z, radius, normal, p1, pointLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
			}
			
			switch (numDL) {
				case 5:
					diffuse = getDiffuse(j, i, z, radius, normal, d5, directionalLight);
					ambient = getAmbient(d5);
					specular = getSpecular(j, i, z, radius, normal, d5, directionalLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
				case 4:
					diffuse = getDiffuse(j, i, z, radius, normal, d4, directionalLight);
					ambient = getAmbient(d4);
					specular = getSpecular(j, i, z, radius, normal, d4, directionalLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
				case 3:
					diffuse = getDiffuse(j, i, z, radius, normal, d3, directionalLight);
					ambient = getAmbient(d3);
					specular = getSpecular(j, i, z, radius, normal, d3, directionalLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
				case 2:
					diffuse = getDiffuse(j, i, z, radius, normal, d2, directionalLight);
					ambient = getAmbient(d2);
					specular = getSpecular(j, i, z, radius, normal, d2, directionalLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
				case 1:
					diffuse = getDiffuse(j, i, z, radius, normal, d1, directionalLight);
					ambient = getAmbient(d1);
					specular = getSpecular(j, i, z, radius, normal, d1, directionalLight);
					
					red += diffuse[0] + ambient[0] + specular[0];
					green += diffuse[1] + ambient[1] + specular[1];
					blue += diffuse[2] + ambient[2] + specular[2];
			}
			
			setPixel(x + j, y + i, red, green, blue);
			
		}
	}
	glEnd();
	/*
	 // Draw border, using line strip primitive
	 glBegin(GL_LINE_STRIP);
	 
	 
	 // White border
	 glColor3f(1.0f, 1.0f, 1.0f);
	 //glVertex2f(x, y);
	 for (int i = 0; i <= 360; i++)
	 {
	 // Need to perform similar coordinate conversion
	 float radian = i*PI/180.0f;
	 glVertex2f(x + cos(radian)*radius,y + sin(radian)*radius);
	 }
	 
	 glEnd();
	 */
}

static float* getAmbient(const float (&argVector)[6]) {
	float* ambientRGB = new float[3];
	ambientRGB[0] = ka[0] * argVector[3];
	ambientRGB[1] = ka[1] * argVector[4];
	ambientRGB[2] = ka[2] * argVector[5];
	return ambientRGB;
}

static float* getDiffuse(int x, int y, int z, int radius, 
						 const float (&normal)[3],
						 const float (&argVector)[6],
						 typeOfLight type) {
	
	float* diffuseRGB = new float[3];
	
	float tempVec[3];
	if (type == directionalLight) {
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
	tempVec[0] = max(kd[0] * argVector[3] * temp, 0.0f);
	tempVec[1] = max(kd[1] * argVector[4] * temp, 0.0f);
	tempVec[2] = max(kd[2] * argVector[5] * temp , 0.0f);
	
	diffuseRGB[0] = tempVec[0];
	diffuseRGB[1] = tempVec[1];
	diffuseRGB[2] = tempVec[2];
	
	return diffuseRGB;
	
}

static float* getSpecular(int x, int y, int z, int radius, 
						  const float (&normal)[3], const float (&argVector)[6],
						  typeOfLight type) {
	float* specularRGB = new float[3];
	float* lightV = new float[3];
	if (type == directionalLight) {
		lightV[0]=-argVector[0]*radius;
		lightV[1]=-argVector[1]*radius;
		lightV[2]=-argVector[2]*radius;
	} else {
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
	specterm = pow(specterm, (int)specPowerCoefficient);
	specularRGB[0] = ks[0]*argVector[3]*specterm;
	specularRGB[1] = ks[1]*argVector[4]*specterm;
	specularRGB[2] = ks[2]*argVector[5]*specterm;
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




//****************************************************
// function that does the actual drawing of stuff
//***************************************************

void myDisplay() {
	
	glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer
	
	glMatrixMode(GL_MODELVIEW);					// indicate we are specifying camera transformations
	glLoadIdentity();							// make sure transformation is "zero'd"
	
	plotX = viewport.w/2;
	plotY = viewport.h/2;
	// Start drawing
	circle(plotX, plotY, min(viewport.w, viewport.h)/2);
	
	glFlush();
	glutSwapBuffers();					// swap buffers (we earlier set double buffer)
	glutKeyboardFunc(exitWindow);
	
}

void exitWindow(unsigned char key, int x, int y){
	if (key == ' ') {
		exit(0);
	}
	
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************

int main(int argc, char *argv[]) {
	
	
	int index = 1;
    while(index != argc){
		string component = argv[index];
		cout << component << endl;
        if(component.compare("-ka")==0){
            ka[0] = atof(argv[index+1]);
            ka[1] = atof(argv[index+2]);
            ka[2] = atof(argv[index+3]);
            index += 4;
        }
        else if(component.compare("-kd")==0){
            kd[0] = atof(argv[index+1]);
            kd[1] = atof(argv[index+2]);
            kd[2] = atof(argv[index+3]);
            index += 4;
        }
        else if(component.compare("-ks")==0){
            ks[0] = atof(argv[index+1]);
            ks[1] = atof(argv[index+2]);
            ks[2] = atof(argv[index+3]);
            index+=4;
        }
        else if((component.compare("-dl")==0) && (numDL == 0)){
            d1[0] = atof(argv[index+1]);
            d1[1] = atof(argv[index+2]);
            d1[2] = atof(argv[index+3]);
            d1[3] = atof(argv[index+4]);
            d1[4] = atof(argv[index+5]);
            d1[5] = atof(argv[index+6]);
            index+=7;
            numDL++;
        }
        else if((component.compare("-dl")==0) && (numDL == 1)){
            d2[0] = atof(argv[index+1]);
            d2[1] = atof(argv[index+2]);
            d2[2] = atof(argv[index+3]);
            d2[3] = atof(argv[index+4]);
            d2[4] = atof(argv[index+5]);
            d2[5] = atof(argv[index+6]);
            index+=7;
            numDL++;
        }
        else if((component.compare("-dl")==0) && (numDL == 2)){
            d3[0] = atof(argv[index+1]);
            d3[1] = atof(argv[index+2]);
            d3[2] = atof(argv[index+3]);
            d3[3] = atof(argv[index+4]);
            d3[4] = atof(argv[index+5]);
            d3[5] = atof(argv[index+6]);
            index+=7;
            numDL++;
        }
        else if((component.compare("-dl")==0) && (numDL == 3)){
            d4[0] = atof(argv[index+1]);
            d4[1] = atof(argv[index+2]);
            d4[2] = atof(argv[index+3]);
            d4[3] = atof(argv[index+4]);
            d4[4] = atof(argv[index+5]);
            d4[5] = atof(argv[index+6]);
            index+=7;
            numDL++;
        }
        else if((component.compare("-dl")==0) && (numDL == 4)){
            d5[0] = atof(argv[index+1]);
            d5[1] = atof(argv[index+2]);
            d5[2] = atof(argv[index+3]);
            d5[3] = atof(argv[index+4]);
            d5[4] = atof(argv[index+5]);
            d5[5] = atof(argv[index+6]);
            index+=7;
            numDL++;
        }
        else if((component.compare("-pl")==0) && (numPL == 0)){
            p1[0] = atof(argv[index+1]);
            p1[1] = atof(argv[index+2]);
            p1[2] = atof(argv[index+3]);
            p1[3] = atof(argv[index+4]);
            p1[4] = atof(argv[index+5]);
            p1[5] = atof(argv[index+6]);
            index+=7;
            numPL++;
        }
        else if((component.compare("-pl")==0) && (numPL == 1)){
            p2[0] = atof(argv[index+1]);
            p2[1] = atof(argv[index+2]);
            p2[2] = atof(argv[index+3]);
            p2[3] = atof(argv[index+4]);
            p2[4] = atof(argv[index+5]);
            p2[5] = atof(argv[index+6]);
            index+=7;
            numPL++;
        }
        else if((component.compare("-pl")==0) && (numPL == 2)){
            p3[0] = atof(argv[index+1]);
            p3[1] = atof(argv[index+2]);
            p3[2] = atof(argv[index+3]);
            p3[3] = atof(argv[index+4]);
            p3[4] = atof(argv[index+5]);
            p3[5] = atof(argv[index+6]);
            index+=7;
            numPL++;
        }
        else if((component.compare("-pl")==0) && (numPL == 3)){
            p4[0] = atof(argv[index+1]);
            p4[1] = atof(argv[index+2]);
            p4[2] = atof(argv[index+3]);
            p4[3] = atof(argv[index+4]);
            p4[4] = atof(argv[index+5]);
            p4[5] = atof(argv[index+6]);
            index+=7;
            numPL++;
        }
        else if((component.compare("-pl")==0) && (numPL == 4)){
            p5[0] = atof(argv[index+1]);
            p5[1] = atof(argv[index+2]);
            p5[2] = atof(argv[index+3]);
            p5[3] = atof(argv[index+4]);
            p5[4] = atof(argv[index+5]);
            p5[5] = atof(argv[index+6]);
            index+=7;
            numPL++;
        }else if(component.compare("-sp")==0){
            specPowerCoefficient = atof(argv[index+1]);
            index+=2;
        }
	}
	
  	//This initializes glut
  	glutInit(&argc, argv);
	
  	//This tells glut to use a double-buffered window with red, green, and blue channels 
  	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(24);
	
  	// Initalize theviewport size
  	viewport.w = 400;
  	viewport.h = 400;
	
  	//The size and position of the window
  	glutInitWindowSize(viewport.w, viewport.h);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow(argv[0]);
	
	
  	initScene();							// quick function to set up scene
	
  	glutDisplayFunc(myDisplay);					// function to run when its time to draw something
  	glutReshapeFunc(myReshape);					// function to run when the window gets resized			
	
  	glutMainLoop();							// infinite loop that will keep drawing and resizing and whatever else
	
  	return 0;
}
