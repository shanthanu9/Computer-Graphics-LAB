#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INTERVAL 0.01
#define XMAX 300
#define YMAX 300
#define INIT_SIZE 10

const float PI = 3.14159265;

float scale = 1;
float tx = 0, ty = 0;

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -XMAX, XMAX, -YMAX, YMAX );
    glFlush();
}

float rotatex(float angle, float x, float y) {
    angle = PI / 180.0 * angle;
    return x*cos(angle)-y*sin(angle);
}

float rotatey(float angle, float x, float y) {
    angle = PI / 180.0 * angle;
    return x*sin(angle)+y*cos(angle);
}

void printxy(float x, float y) {
    printf("(%f, %f)\n", x, y);
}

void drawEquiTriangle(float sx, float sy) {
    float tempx, tempy;
    glBegin(GL_TRIANGLES);
        float x = sx, y = sy;
        glVertex2f(x, y);
        
        tempx = rotatex(120, x, y);
        tempy = rotatey(120, x, y);
        x = tempx; y = tempy;
        glVertex2f(x, y);

        tempx = rotatex(120, x, y);
        tempy = rotatey(120, x, y);
        x = tempx; y = tempy;
        glVertex2f(x, y);
    glEnd();
}

void drawStar(int x, int y) {

    // glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // glRotatef(angle, 0, 0, 1);
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 0);

    drawEquiTriangle(0, INIT_SIZE);
    drawEquiTriangle(0, -INIT_SIZE);

    glTranslatef(-x, -y, 0);

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    x -= XMAX;
    y -= YMAX; y = -y;
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                drawStar(x, y);
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                exit(1);
            break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    if(key == 'S')
        scale += 0.1;
    if(key == 'R')
        scale -= 0.1;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(2*XMAX, 2*YMAX);
    glutCreateWindow("Stars");

    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    initGL();
    glutMainLoop();
    return 0;
}