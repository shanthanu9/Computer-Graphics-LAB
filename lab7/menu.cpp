#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0

int x1, x2;
int y1, y2;

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -250, 250, -250, 250 );
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int menu;

    menu = glutCreateMenu(processMenuEvents);

    
    
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Menu");

    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}