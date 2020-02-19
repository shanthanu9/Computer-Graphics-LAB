#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define INTERVAL 0.01

float angle = 0, factor = INTERVAL, scale = 1;

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -250, 250, -250, 250 );
}

void mouse(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                scale += 0.1;
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                scale -= 0.1;
            break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    if(key == 'k')
        scale += 0.1;
    if(key == 'l')
        scale -= 0.1;
}

void idle() {
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glRotatef(angle, 0, 0, 1);
        glScalef(scale, scale, 0);
        glBegin(GL_POLYGON);
            glVertex2f(50, 50);
            glVertex2f(-50, 50);
            glVertex2f(-50, -50);
            glVertex2f(50, -50);
        glEnd();
    glPopMatrix();

    printf("%f\n", scale);

    angle += factor;
    angle = (angle > 360)?(angle-360):(angle);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Learn");

    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    initGL();
    glutMainLoop();
    return 0;
}