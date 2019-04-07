/// ------------------------- THE FOLLOWING IS VORONOI DIAGRAM PROGRAM --------------------------------------------------------------------
//**
#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>


#include "Voronoi.h"
#include "VPoint.h"

void display (void);
void onEF (int n);
void reshape (int width, int height);

vor::Voronoi * v;
vor::Vertices * ver; // vertices
vor::Edges * edg;	 // diagram edges

double w = 10000;
const int Sites = 100;

int main (int argc, char **argv)
{
	using namespace vor;

	v = new Voronoi();
	ver = new Vertices();

	srand ( time(NULL) );

	for(int i=0; i < Sites; i++)
	{
		ver->push_back(new VPoint( w * (double)rand()/(double)RAND_MAX , w * (double)rand()/(double)RAND_MAX ));
	}

	edg = v->GetEdges(ver, w, w);
	std::cout << "voronois done!\n";

	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i)
	{
			if( (*i)->start == 0 )
			{
				std::cout << "missing the start of the edge!\n";
				continue;
			}
			if( (*i)->end == 0 )
			{
				std::cout << "missing the end of the edge!\n";
				continue;
			}
	}

	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (600, 600); // Set the width and height of the window
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("Your first OpenGL Window"); // Set the title for the window

	glutTimerFunc(100, onEF, 0);
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering

	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping

	//glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
	//glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events

	glutMainLoop(); // Enter GLUT's main loop

	return 0;
}

void drawVoronoi()
{

    /**
	vor::Vertices::iterator j = dir->begin();
	for(vor::Vertices::iterator i = ver->begin(); i != ver->end(); ++i)
	{
		(*i)->x += (*j)->x * w/50;
		(*i)->y += (*j)->y * w/50;
		if( (*i)->x > w ) (*j)->x *= -1;
		if( (*i)->x < 0 ) (*j)->x *= -1;

		if( (*i)->y > w ) (*j)->y *= -1;
		if( (*i)->y < 0 ) (*j)->y *= -1;
		++j;
	}  **/


	edg = v->GetEdges(ver, w, w);
	//std::cout << "voronoi done";
	//**
	for(vor::Vertices::iterator i = ver->begin(); i!= ver->end(); ++i)
	{
		glBegin(GL_QUADS);
		//std::cout << (*i)->x << "\n";
		glVertex2f( -1+2*(*i)->x/w -0.01,  -1+2*(*i)->y/w - 0.01);
		glVertex2f( -1+2*(*i)->x/w +0.01,  -1+2*(*i)->y/w - 0.01);
		glVertex2f( -1+2*(*i)->x/w +0.01,  -1+2*(*i)->y/w + 0.01);
		glVertex2f( -1+2*(*i)->x/w -0.01,  -1+2*(*i)->y/w + 0.01);
		glEnd();
	}   //**/

    //**
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i)
	{
		/**   This cycle builds the Dilone triangulation
		glBegin(GL_LINES);
		glVertex2f( -1+2*(*i)->left->x/w,  -1+2*(*i)->left->y/w);
		glVertex2f( -1+2*(*i)->right->x/w, -1+2*(*i)->right->y/w);
		glEnd();
		**/ //  <<-----------------------------------------------------------------------------
		//**
		glBegin(GL_LINES);
		glVertex2f( -1+2*(*i)->start->x/w,  -1+2*(*i)->start->y/w);
		glVertex2f( -1+2*(*i)->end->x/w, -1+2*(*i)->end->y/w);
		glEnd();
		//**/

	}
	//**/
}

void display (void)
{
	std::cout << "display\n";
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
	glTranslatef(0.0f, 0.0f, -5.0f);

	glFlush();
}


void onEF(int n)
{

	glutTimerFunc(20, onEF, 0);
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Clear the background of our window to red

	drawVoronoi();
	glutSwapBuffers();
	//Draw everything to the screen
}

void reshape (int width, int height)
{

	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective(22.5, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}
//**/
///

///-------------------------------------------------------------------------------------------------------------------- END OF PROGRAM


















/**
#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <math.h>
#include <algorithm>

#define PI 3.14159265
#define gd 10
#define gr 6
#define fn 3000


int tim = 0;

struct sf // snowflake
{
	float size, rot, x, y, z;
	sf()
	{
		size = 0.3 + 0.7*rand()/RAND_MAX;
		x = 8.0 * rand()/RAND_MAX - 4;
		y = 4.0 * rand()/RAND_MAX - 2;
		z = 4.0 * rand()/RAND_MAX - 2;
		rot = 0;
	}
	void iterate()
	{
		y -= gd * 0.0005;
		x += gr * 0.0005;
		if(y<-2) y = 2 + 0.3*rand()/RAND_MAX;
		if(x>4) x = -4 + 0.3*rand()/RAND_MAX;
		rot -= 0.03;
	}
	bool operator < (sf & a) {	return z < a.z; }

} flakes [fn];

void dl(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void dc(GLfloat x, GLfloat y, float r);
void df(sf & f);

void display (void)
{
	std::cout << "display\n";
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
	glTranslatef(0.0f, 0.0f, -5.0f);
}

void onEF(int n)
{
	glutTimerFunc(5, onEF, 0);
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Clear the background of our window to red
	tim ++;

	glHint (GL_POLYGON_SMOOTH, GL_DONT_CARE);
	glLineWidth (1.5);

	double c;
	for(int i=0; i<fn; i++)
	{
		flakes[i].iterate();
		df(flakes[i]);
	}


	glutSwapBuffers();//Draw everything to the screen
}

void reshape (int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective(22.5, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}


int main (int argc, char **argv)
{
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_DOUBLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (600, 600); // Set the width and height of the window
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("Snìžení od Ivana"); // Set the title for the window

	glutDisplayFunc(display); // Tell GLUT to use the method "display" for
	glutTimerFunc(5, onEF, 0);
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for rendering

	std::sort(flakes, flakes + fn);

	glutMainLoop(); // Enter GLUT's main loop
}


void dl(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    glColor3f(0.8f,0.8f,0.8f);//black color
	glLineWidth(7); //5 pixels
	glBegin(GL_LINES);
    glVertex2f(x1+0.006,y1-0.006);
    glVertex2f(x2+0.006,y2-0.006);
	glColor3f(0,0,0);//black color
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}

void dc(GLfloat x, GLfloat y, float r)
{
    glBegin(GL_TRIANGLE_FAN);
    glLineWidth(3);

	float deg;
    for(int i=0;i<=360;i += 20) //no of short lines to be drawn
    {
		deg = i*(2*PI/360);
        glVertex2f(x + r * cos(deg), y + r * sin(deg));
    }
    glEnd();
}

void df(sf & f)
{
    glLineWidth(3);
	float c = (f.z + 2)/4;
	float deg, r, nx, ny;
	glColor3f(0.2+c,0.2+c,0.4+c);

	glBegin(GL_LINES);
	for(int i=0; i<3; i++)
	{
		deg = (360/6)*i*(2*PI/360) + f.rot;
		r = (0.5+c/2)*f.size/50;
		glVertex3f(f.x + r*cos(deg), f.y + r * sin(deg), f.z);
		glVertex3f(f.x - r*cos(deg), f.y - r * sin(deg), f.z);
	}
	glEnd();
}
**/

/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
/**
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;
**/
/* GLUT callback Handlers */

/**
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
**/
/* Program entry point */
/**
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
**/
