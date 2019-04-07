
#include "freeglut.h"
#include <iostream>
#include <time.h>

#include "Kirpatrick.h"
#include "Graham.h"
#include "Andrew_Jarv.h"
#include "Recursive.h"

using namespace std;


vector<Point> init_points;
vector<Point> hull;
vector<Point> hull_K, hull_G, hull_A, hull_R;
vector<vector<Point>> all_hulls;
const double point_Size = 0.01; // = 0.04 / 0.008
const int points = 50;

void reshape (int width, int height);
void display (void);
void drawHULL();
void onEF();


///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void drawHULL()
{
    int h = hull.size(), p = init_points.size();
    for (int i = 0; i < p; ++i)
    {
        glBegin(GL_QUADS);
        glVertex2f( init_points[i].x + point_Size , init_points[i].y + point_Size);
        glVertex2f( init_points[i].x - point_Size , init_points[i].y + point_Size);
        glVertex2f( init_points[i].x - point_Size , init_points[i].y - point_Size);
        glVertex2f( init_points[i].x + point_Size , init_points[i].y - point_Size);
        glEnd();
        /**
        glBegin(GL_POINT);
        glPointSize(point_Size);
        glVertex2f( hull[i].x, hull[i].y );
        glEnd();
        **/
    }
    for (int i = 0; i < h; ++i)
    {
        glBegin(GL_LINES);
		glVertex2f( hull[i].x , hull[i].y );
		glVertex2f( hull[(i+1)%h].x , hull[(i+1)%h].y );
		glEnd();
    }
}

void drawALLHULLS()
{
    pair<double,double> displacement[4] = { {0,0}, {0,1.5}, {1.5,0}, {1.5,1.5} };
    int k = 0;
    for (auto h: all_hulls)
    {
        int h0 = h.size(), p = init_points.size();
        for (int i = 0; i < p; ++i)
        {
            glBegin(GL_QUADS);
            glVertex2f( init_points[i].x + point_Size + displacement[k].first, init_points[i].y + point_Size + displacement[k].second );
            glVertex2f( init_points[i].x - point_Size + displacement[k].first, init_points[i].y + point_Size + displacement[k].second );
            glVertex2f( init_points[i].x - point_Size + displacement[k].first, init_points[i].y - point_Size + displacement[k].second );
            glVertex2f( init_points[i].x + point_Size + displacement[k].first, init_points[i].y - point_Size + displacement[k].second );
            glEnd();
        }
        for (int i = 0; i < h0; ++i)
        {
            glBegin(GL_LINES);
            glVertex2f( h[i].x + displacement[k].first, h[i].y + displacement[k].second );
            glVertex2f( h[(i+1)%h0].x + displacement[k].first, h[(i+1)%h0].y + displacement[k].second );
            glEnd();
        }
        ++k;
    }
}

void display (void)
{
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Clear the background of our window to red
    glClear(GL_COLOR_BUFFER_BIT);//Clear the screen

	//drawHULL();
	drawALLHULLS();

	glutSwapBuffers();
	glFlush();
}

void reshape (int width, int height)
{

	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	//glOrtho(-2, 5, -2, 5, -1, 10);
	//glOrtho(-0.5, 1.5, -0.5, 1.5, -1, 10);
	glOrtho(-0.5, 3, -0.5, 3, -1, 10);
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void onEF()
{
	glutPostRedisplay();
	//Draw everything to the screen
}
///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


int main(int argc, char **argv)
{
    /*
    Point p1{0,0}, p2{1,0}, p3{1,1};
    cout<<endl<<orientation(p3,p2,p1);
    cout<<endl<<clockwise(p3,p2,p1);
    cout<<endl<<counterclockwise(p3,p2,p1)<<endl;
    */

    //init_points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}, {2, 4}, {-1, 3}};
    /*
    srand(5);
    for(int i=0; i < points; i++)
	{
	    Point p{ rand()%7 - 2, rand()%7 - 2 };
		init_points.push_back(p);
	}
    */
    //*
    srand(7);
    for(int i=0; i < points; i++)
	{
	    Point p{ (double)rand()/(double)RAND_MAX , (double)rand()/(double)RAND_MAX };
		init_points.push_back(p);
	}
    //*/
    //*
    convexHull_K (init_points, hull_K);
    convexHull_G (init_points, hull_G);
    convexHull_AJ(init_points, hull_A);
    convexHull_R (init_points, hull_R);
    all_hulls.resize(0);
    all_hulls.push_back(hull_K);
    all_hulls.push_back(hull_G);
    all_hulls.push_back(hull_A);
    all_hulls.push_back(hull_R);
    //*/
    /*
    //vector<Point> hull_K; convexHull_K (init_points, hull_K); hull = hull_K;
    //vector<Point> hull_G; convexHull_G (init_points, hull_G); hull = hull_G;
    //vector<Point> hull_A; convexHull_AJ(init_points, hull_A); hull = hull_A;
    //vector<Point> hull_R; convexHull_R (init_points, hull_R); hull = hull_R;
    */
    glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize(600, 600); // Set the width and height of the window
	glutInitWindowPosition(100, 100); // Set the position of the window
	glutCreateWindow("OpenGL Window"); // Set the title for the window
	//glEnable( GL_POINT_SMOOTH );

	glutIdleFunc(onEF);
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
	glutMainLoop(); // Enter GLUT's main loop

    return 0;
}
