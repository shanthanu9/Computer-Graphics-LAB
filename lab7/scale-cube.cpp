#include <GL/glut.h>
#include "transformation.hpp"
#include <stdio.h>

/* Global variables */
char title[] = "3D Shapes";
float s;
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
 
void scaleAndPlot( float x, float y, float z ) {
    // glVertex2i(x, y);

    struct point in = {x, y, z}, out = {0, 0, 0};
    struct point sc = {s, s, s};
    scale(in, sc, &out);

    glVertex3f(out.x, out.y, out.z);
    // glVertex3f(x, y, z);
}


void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
 
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      scaleAndPlot( 1.0f, 1.0f, -1.0f);
      scaleAndPlot(-1.0f, 1.0f, -1.0f);
      scaleAndPlot(-1.0f, 1.0f,  1.0f);
      scaleAndPlot( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      scaleAndPlot( 1.0f, -1.0f,  1.0f);
      scaleAndPlot(-1.0f, -1.0f,  1.0f);
      scaleAndPlot(-1.0f, -1.0f, -1.0f);
      scaleAndPlot( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      scaleAndPlot( 1.0f,  1.0f, 1.0f);
      scaleAndPlot(-1.0f,  1.0f, 1.0f);
      scaleAndPlot(-1.0f, -1.0f, 1.0f);
      scaleAndPlot( 1.0f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      scaleAndPlot( 1.0f, -1.0f, -1.0f);
      scaleAndPlot(-1.0f, -1.0f, -1.0f);
      scaleAndPlot(-1.0f,  1.0f, -1.0f);
      scaleAndPlot( 1.0f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      scaleAndPlot(-1.0f,  1.0f,  1.0f);
      scaleAndPlot(-1.0f,  1.0f, -1.0f);
      scaleAndPlot(-1.0f, -1.0f, -1.0f);
      scaleAndPlot(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      scaleAndPlot(1.0f,  1.0f, -1.0f);
      scaleAndPlot(1.0f,  1.0f,  1.0f);
      scaleAndPlot(1.0f, -1.0f,  1.0f);
      scaleAndPlot(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
 
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   
   if(argc == 2) {
        s = atof(argv[1]);
    }
    else {
        printf("usage: ./a.out scale\n");
        return 1;
    }
   
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}