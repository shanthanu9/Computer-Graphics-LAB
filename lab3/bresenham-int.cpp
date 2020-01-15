#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0
#define max(a, b) ((a>b)?a:b)
#define min(a, b) ((a<b)?a:b)

int x1, x2;
int y1, y2;

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, 500.0, 0.0, 500.0 );
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int dx = x2 - x1;
    int dy = y2 - y1;
    float fractional_inc = 2 * (dy) * sign(dy);
    float fraction = 2 * dy * sign(dy) - dx * sign(dx);

    glBegin(GL_POINTS);
        glColor3f(1,1,1);
        int x = x1, y = y1;
        for(int x = min(x1, x2); x < max(x1, x2); x += 1 * sign(dx)) {
            glVertex2i(x, y);
            fraction += fractional_inc;
            if(fraction >= 0) {
                y = y + 1 * sign(dy);
                fraction -= 2 * dx * sign(dx);
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
    glutCreateWindow("DDA Line drawing");

    if(argc == 5) {
        x1 = atoi(argv[1]);
        y1 = atoi(argv[2]);
        x2 = atoi(argv[3]);
        y2 = atoi(argv[4]);
    }
    else {
        printf("usage: ./a.out x1 y1 x2 y2\n");
        return 1;
    }

    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}