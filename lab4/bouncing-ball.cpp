#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0
#define max(a, b) ((a>b)?a:b)
#define min(a, b) ((a<b)?a:b)

int pos = 150, dir = 0;
int delay = 10000, rate = 30;

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

void drawLine(int x1, int y1, int x2, int y2) {
    
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
            glVertex2i(x, y);
            x += xi;
            y += yi;
        }
    glEnd();
}

void idle() {
    glutPostRedisplay();
    usleep(delay);
}

void display() {
    while(1) {
        
        glClear(GL_COLOR_BUFFER_BIT);

        drawLine(-250, -200, 250, -200);

        drawCircle(0, pos, 50);

        if(dir == 0) {
            if(pos > -150) {
                pos--;
            }
            else {
                dir = 1;
                pos++;
            }
            // rate += 1;
            delay -= rate;
        }
        else {
            if(pos < 150) {
                pos++;
            }
            else {
                dir = 0;
                pos--;
            }
            // rate -= 1;
            delay += rate;
        }

        usleep(delay);

        glFlush();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Pendulum");

    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    initGL();
    glutMainLoop();
    return 0;
}