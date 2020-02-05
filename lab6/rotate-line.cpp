#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "transformation.hpp"

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0

int x1, x2;
// y1 is used in math lib -_-
int y11, y2;
int angle;

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -250, 250, -250, 250 );
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int dx = x2 - x1;
    int dy = y2 - y11;
    float xi, yi;
    int steps;
    if(abs(dx) > abs(dy)) {
        steps = abs(dx);
        xi = 1 * sign(dx);
        yi = abs((float)dy/dx) * sign(dy);
    }
    else {
        steps = abs(dy);
        xi = abs((float)dx/dy) * sign(dx);
        yi = 1 * sign(dy);
    }

    glBegin(GL_POINTS);
        glColor3f(1,1,1);
        float x = x1, y = y11;
        for(int i = 0; i <= steps; i++) {

            struct point in = {x, y}, out = {0, 0};
            rotate(in, angle, &out);

            glVertex2i(x, y);
            glVertex2i(out.x, out.y);
            x += xi;
            y += yi;
        }
    glEnd();
    
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line drawing");

    if(argc == 6) {
        x1 = atoi(argv[1]);
        y11 = atoi(argv[2]);
        x2 = atoi(argv[3]);
        y2 = atoi(argv[4]);
        angle = atoi(argv[5]);
    }
    else {
        printf("usage: ./a.out x1 y1 x2 y2 angle\n");
        return 1;
    }

    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}