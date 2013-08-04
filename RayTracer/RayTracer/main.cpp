#include <iostream>
#include <Eigen/Dense>
#include <time.h>
#include <math.h>
#include <vector>
#include "RayTracer.h"
#include "Sphere.h"
#include "Ray.h"
#include "PhongIllumination.h"
#include "Lights.h"
#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

using namespace Eigen;
using namespace std;

#define PI 3.14159265

class Viewport {
public:
	int w, h; // width and height
};

void exitWindow(unsigned char key, int x, int y);
void setPixel(int, int, GLfloat, GLfloat, GLfloat);


//GLOBALS
Viewport viewport;
int Eye[] = { 0, 0, 0 };
float LL[] = { -1.0f, -1.0f, 0.0f };
float UL[] = { -1.0f,  1.0f, 0.0f };
float LR[] = {  1.0f, -1.0f, 0.0f };
float UR[] = {  1.0f,  1.0f, 0.0f };


//takes in dimentions of the render scene
void startRayTrace( int x, int y ) {
	
	glBegin(GL_POINTS);
	
	float ambient[]  = { 1.0f, 1.0f, 1.0f };
	float diffuse[]  = { 1.0f, 1.0f, 1.0f };
	float specular[] = { 1.4f, 1.4f, 1.7f };
	
	Sphere sphere = Sphere( 1.0f, 0.0f, 0.0f, -2.0f, ambient, specular, diffuse, 1.0f );
	
	
	cout << sphere.ka[0] << endl;
	cout << sphere.ka[1] << endl;
	cout << sphere.ka[2] << endl;
	cout << sphere.kd[0] << endl;
	cout << sphere.kd[1] << endl;
	cout << sphere.kd[2] << endl;
	cout << sphere.ks[0] << endl;
	cout << sphere.ks[1] << endl;
	cout << sphere.ks[2] << endl;
	
	
	
	
	vector< Sphere* > spherePointers;
	vector< Light* > lightPointers;
	spherePointers.push_back( &sphere );
	DirectionalLight* dl = new DirectionalLight( 1.4f, 1.0f, 3.5f, 0.6f, 0.7f, 0.9f );
	lightPointers.push_back( dl );
	
	
	cout << lightPointers[0]->getXYZ() << endl;
	cout << lightPointers[0]->rgb << endl;
	cout << endl;
	cout << dl->rgb << endl;
	
	
	float t;
	RayTracer raytracer( spherePointers );
	
	for ( int i=0; i < x; ++i ) {
		for ( int j=0 ; j < y; ++j ) {
			
			Ray ray_world = raytracer.generateRay( i, j, viewport.w, viewport.h );
			
			if ( raytracer.intersectionP( ray_world ) ) {
				Sphere* intersectedSphere;
				t = raytracer.intersection( ray_world, intersectedSphere );
				Vector3f color = sphereShading( ray_world.d(0), ray_world.d(1), &sphere, lightPointers );
				cout << color << endl;
				setPixel( i, j, color(0), color(1), color(2) );
			}
			
		}
	}
	glEnd();
	
}


void myDisplay() {
    
    glClear(GL_COLOR_BUFFER_BIT);                // clear the color buffer
    
    glMatrixMode(GL_MODELVIEW);                    // indicate we are specifying camera transformations
    glLoadIdentity();                            // make sure transformation is "zero'd"
	
	
	
	
	startRayTrace(viewport.w, viewport.h);
	
	glutKeyboardFunc(exitWindow);
    
    glFlush();
    glutSwapBuffers();                    // swap buffers (we earlier set double buffer)
}

void exitWindow(unsigned char key, int x, int y){
	if (key == ' ') {
		exit(0);
	}
	
}

void initScene(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent
    
    glViewport (0,0,viewport.w,viewport.h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,viewport.w, 0, viewport.h);
}

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


int main(int argc, char *argv[]) {
    
	
	//This initializes glut
	glutInit(&argc, argv);
    
	//This tells glut to use a double-buffered window with red, green, and blue channels 
	glutInitDisplayMode(24);
    
	// Initalize theviewport size
	viewport.w = 400;
	viewport.h = 400;
    
	//The size and position of the window
	glutInitWindowSize(viewport.w, viewport.h);
	glutInitWindowPosition(0,0);
	glutCreateWindow(argv[0]);
    
    
	initScene();                            // quick function to set up scene
    
	glutDisplayFunc(myDisplay);                    // function to run when its time to draw something
	glutReshapeFunc(myReshape);                    // function to run when the window gets resized            
    
	glutMainLoop();                            // infinite loop that will keep drawing and resizing and whatever else
    
	return 0;
}