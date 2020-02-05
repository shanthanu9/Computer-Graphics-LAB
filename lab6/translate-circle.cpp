#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "transformation.hpp"

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0
#define max(a, b) ((a>b)?a:b)
#define min(a, b) ((a<b)?a:b)

int cx, cy, r, tx, ty;

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -250, 250, -250, 250 );
}

void plotPointAndTranslate(int x, int y) {

    glVertex2i(x, y);

    struct point in = {x, y}, out = {0, 0};
    struct point t = {tx, ty};
    translate(in, t, &out);

    glVertex2i(out.x, out.y);
}

void plot8SymPoints(int x, int y) {
    plotPointAndTranslate(x, y);
    plotPointAndTranslate(-x, y);
    plotPointAndTranslate(x, -y);
    plotPointAndTranslate(-x, -y);
    plotPointAndTranslate(y, x);
    plotPointAndTranslate(-y, x);
    plotPointAndTranslate(y, -x);
    plotPointAndTranslate(-y, -x);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int d = 3 - 2*r;
    int x = 0, y = r;
    
    glTranslatef(cx, cy, 0.0f);
    glBegin(GL_POINTS);
        while(x <= y) {
            plot8SymPoints(x, y);
            x++;
            if(d < 0) {
                d = d + 4*x + 6;
            }   
            else {
                d = d + 4*(x-y) + 10;
                y--;
            }
        }
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenhem circle drawing");

    if(argc == 6) {
        cx = atoi(argv[1]);
        cy = atoi(argv[2]);
        r = atoi(argv[3]);
        tx = atoi(argv[4]);
        ty = atoi(argv[5]);
    }
    else {
        printf("usage: ./a.out cx cy radius tx ty\n");
        return 1;
    }

    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}