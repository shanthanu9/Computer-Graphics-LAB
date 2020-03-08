#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0

int xmin = -75, xmax = 75;
int ymin = -50, ymax = 50;

int x1, x2;
int y1, y2;

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -250, 250, -250, 250 );
}

void drawClippingRegion() {
    glBegin(GL_LINES);

    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);

    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);

    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);

    glVertex2f(xmin, ymax);
    glVertex2f(xmin, ymin);

    glEnd();
}

int getRegionCode(float x, float y) {
    int code = 0;

    if(y > ymax) {
        code |= 8;
    }
    if(y < ymin) {
        code |= 4;
    }
    if(x > xmax) {
        code |= 2;
    }
    if(x < xmin) {
        code |= 1;
    }

    return code;
}

void drawLine(float x1, float y1, float x2, float y2, bool color) {
    // color : 1 -> green, 0 -> red

    glBegin(GL_LINES);
    
    if(color == true) glColor3f(0, 1, 0);
    else glColor3f(1, 0, 0);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2); 

    glEnd();
}

void drawClippedLine(int x1, int y1, int x2, int y2) {
    int code1 = getRegionCode(x1, y1);
    int code2 = getRegionCode(x2, y2);

    // line is fully inside clipping area
    if (code1 == 0 && code2 == 0) {
        drawLine(x1, y1, x2, y2, true);
    }
    // line is fully outside
    else if((code1 & code2) != 0) {
        drawLine(x1, y1, x2, y2, false);
    }
    // line is partially inside
    else {
        // left boundary
        if(((x1-xmin)^(x2-xmin)) < 0) {
            int y = y1 + (1.0*(y2-y1))/(1.0*(x2-x1))*(xmin-x1);
            
            if(x1 < xmin) {
                drawLine(x1, y1, xmin, y, false);
                x1 = xmin;
                y1 = y;
            }
            else {
                drawLine(x2, y2, xmin, y, false);
                x2 = xmin;
                y2 = y;
            }
        }
        // right boundary
        if(((x1-xmax)^(x2-xmax)) < 0) {
            
            int y = y1 + (1.0*(y2-y1))/(1.0*(x2-x1))*(xmax-x1);
            
            if(x1 > xmax) {
                drawLine(x1, y1, xmax, y, false);
                x1 = xmax;
                y1 = y;
            }
            else {
                drawLine(x2, y2, xmax, y, false);
                x2 = xmax;
                y2 = y;
            }
        }
        // bottom boundary
        if(((y1-ymin)^(y2-ymin)) < 0) {
            int x = x1 + (1.0*(x2-x1))/(1.0*(y2-y1))*(ymin-y1);
            
            if(y1 < ymin) {
                drawLine(x1, y1, x, ymin, false);
                x1 = x;
                y1 = ymin;
            }
            else {
                drawLine(x2, y2, x, ymin, false);
                x2 = x;
                y2 = ymin;
            }
        }
        // above boundary
        if(((y1-ymax)^(y2-ymax)) < 0) {
            int x = x1 + (1.0*(x2-x1))/(1.0*(y2-y1))*(ymax-y1);
            
            if(y1 > ymax) {
                drawLine(x1, y1, x, ymax, false);
                x1 = x;
                y1 = ymax;
            }
            else {
                drawLine(x2, y2, x, ymax, false);
                x2 = x;
                y2 = ymax;
            }
        }

        drawClippedLine(x1, y1, x2, y2);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawClippingRegion();
    
    // H
    drawClippedLine(-100, -60, -100, 60);
    drawClippedLine(-100, 0, -60, 0);
    drawClippedLine(-60, -60, -60, 60);
    
    // E
    drawClippedLine(-40, -60, -40, 60);
    drawClippedLine(-40, -60, 0, -60);
    drawClippedLine(-40, 0, 0, 0);
    drawClippedLine(-40, 60, 0, 60);

    // L
    drawClippedLine(20, 60, 20, -60);
    drawClippedLine(20, -60, 60, -60);

    // L
    drawClippedLine(80, 60, 80, -60);
    drawClippedLine(80, -60, 120, -60);

    // 0
    drawClippedLine(140, 60, 140, -60);
    drawClippedLine(180, 60, 180, -60);
    drawClippedLine(140, 60, 180, 60);
    drawClippedLine(140, -60, 180, -60);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Line clip");

    glutDisplayFunc(display);
    initGL();

    glutMainLoop();
    return 0;
}