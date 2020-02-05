#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "transformation.hpp"

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0

int n;
struct point points[100];
int angle;

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -250, 250, -250, 250 );
}

void drawLineAndRotate(struct point p1, struct point p2, int angle) {
    
    int x1 = p1.x, y1 = p1.y;
    int x2 = p2.x, y2 = p2.y;

    int dx = x2 - x1;
    int dy = y2 - y1;
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
        float x = x1, y = y1;
        for(int i = 0; i <= steps; i++) {

            struct point in = {x, y}, out = {0, 0};
            rotate(in, angle, &out);

            glVertex2i(x, y);
            glVertex2i(out.x, out.y);
            x += xi;
            y += yi;
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    for(int i = 0; i < n-1; i++) {
        drawLineAndRotate(points[i], points[i+1], angle);
    }
    drawLineAndRotate(points[n-1], points[0], angle);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);

    printf("Enter number of sides: ");
    scanf("%d", &n);

    printf("Enter %d vertices of polygon:\n", n);
    for(int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        points[i].x = x;
        points[i].y = y;
    }

    printf("Rotation angle: ");
    scanf("%d", &angle);

    glutCreateWindow("DDA Line drawing");
    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}