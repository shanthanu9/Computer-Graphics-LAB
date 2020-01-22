#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0
#define max(a, b) ((a>b)?a:b)
#define min(a, b) ((a<b)?a:b)

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -250, 250, -250, 250 );
}

void plot8SymPoints(int x, int y) {
    glVertex2i(x, y);
    glVertex2i(-x, y);
    glVertex2i(x, -y);
    glVertex2i(-x, -y);
    glVertex2i(y, x);
    glVertex2i(-y, x);
    glVertex2i(y, -x);
    glVertex2i(-y, -x);
}

void drawCircle(int cx, int cy, int r) {
    int d = 3 - 2*r;
    int x = 0, y = r;
    
    glPushMatrix();
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
    glPopMatrix();
}

void drawLine(int x1, int y1, int x2, int y2, int cx, int cy, int r) {

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
            if((x-cx)*(x-cx) + (y-cy)*(y-cy) >= r*r)
                glVertex2i(x, y);
            x += xi;
            y += yi;
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawLine(0, 180, 0, 40, 0, 0, 40);
    drawLine(0, 180, 120, 0, 120, 0, 40);
    drawLine(0, 180, -120, 0, -120, 0, 40);

    drawCircle(120, 0, 40);
    drawCircle(0, 0, 40);
    drawCircle(-120, 0, 40);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Pendulum");

    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}