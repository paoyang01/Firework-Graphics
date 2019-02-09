//---------------------------------------
// Program: firework.cpp
// Purpose: To display fireworks
// Author:  Pao Yang & Some source code from Dr. Gauch
// Date:    February 2019
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//---------------------------------------
// Calculate random value between [min..max]
//---------------------------------------
float myrandrange(float min, float max)
{
   return rand() * (max - min) / RAND_MAX + min;
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glEnable(GL_DEPTH_TEST);
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//---------------------------------------
// Create fireworks
//---------------------------------------
void create_fireworks()
{
     int number_of_fireworks = myrandrange(1, 4); // Random number of fireworks displayed on screen
     int number_of_lines = myrandrange(100, 150); // Random number of lines per firework

     // Arrays used to store the point vertices
     float point_vertex_x[number_of_fireworks] = {}; // Center of firework coordinate X
     float point_vertex_y[number_of_fireworks] = {}; // Center of firework coordinate Y
     float point_vertex_z[number_of_fireworks] = {}; // Center of firework coordinate Z

     // Arrays used to store random colors
     float red[number_of_fireworks] = {};
     float blue[number_of_fireworks] = {};
     float green[number_of_fireworks] = {};

     // Initialize the arrays for random colors and point vertices
     for(int i = 0; i < number_of_fireworks; i++)
     {
       point_vertex_x[i] = myrandrange(-0.5, 0.5);
       point_vertex_y[i] = myrandrange(-0.5, 0.5);
       point_vertex_z[i] = myrandrange(-0.5, 0.5);
       red[i] = myrandrange(0, 1);
       blue[i] = myrandrange(0, 1);
       green[i] = myrandrange(0, 1);
     }

     float r[number_of_fireworks] = {}; // Store the radius for each firework

     // Store the x,y,z, coordinates of the verticies so they could be connected into lines
     float x[number_of_lines] = {};
     float y[number_of_lines] = {};
     float z[number_of_lines] = {};
     float d[number_of_lines] = {};

     // Store the values of the mathematical x,y,z coordinates once calculated
     float X[number_of_lines] = {};
     float Y[number_of_lines] = {};
     float Z[number_of_lines] = {};

     // Initialize the number of lines that would come out of fireworks
     for(int i = 0; i < number_of_lines; i++)
     {
       x[i] = myrandrange(-1.0, 1.0);
       y[i] = myrandrange(-1.0, 1.0);
       z[i] = myrandrange(-1.0, 1.0);
       d[i] = sqrt((x[i] * x[i]) + (y[i]*y[i]) + (z[i]*z[i]));
     }


     // Draw the explosions from the center of each firework
     for(int i = 0; i < number_of_fireworks; i++)
     {
       r[i] = myrandrange(0.2, 0.7); // Controls the size of the fireworks so each will be random size
       glColor3f(red[i], blue[i], green[i]);
       for(int j = 0; j < number_of_lines; j++)
       {
         glBegin(GL_LINES);
         X[j] = (x[j] * r[i])/d[j];
         Y[j] = (y[j] * r[i])/d[j];
         Z[j] = (z[j] * r[i])/d[j];
         glVertex3f(point_vertex_x[i], point_vertex_y[i], point_vertex_z[i]);
         glVertex3f(X[j] + point_vertex_x[i], Y[j] + point_vertex_y[i], Z[j] + point_vertex_z[i]);
         glEnd();
         glFlush();
       }
     }
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   create_fireworks(); // Calling the function to initialize and draw the fireworks
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Fireworks");
   glutDisplayFunc(display);
   init();
   glutMainLoop();
   return 0;
}
