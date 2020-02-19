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

    unsigned char str[] = "Text on screen";
    int w;
    w = glutBitmapLength(GLUT_BITMAP_8_BY_13, str);

    glRasterPos2f(0., 0.);

    // float x = .5; /* Centre in the middle of the window */
    // glRasterPos2f(x - (float) w / 2, 0.);

    glColor3f(1, 1, 1);

    int len = strlen((const char *) str);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
    }
    
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Text");

    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}