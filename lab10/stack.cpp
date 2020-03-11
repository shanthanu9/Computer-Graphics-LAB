#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0

float stack_text_pos[6];
int top = -1;
bool STACK_OVERFLOW = false, STACK_EMPTY = true;
int stack[6];

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -250, 250, -250, 250 );
}

void printText(float x, float y, char text[], bool black=false) {

    if(black) {
        glColor3f(0, 0, 0);
    }

    glRasterPos2f(x, y);

    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }

    if(black) {
        glColor3f(1, 1, 1);
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'i':
            if(top == 5) {
                STACK_OVERFLOW = true;
            }
            else {
                STACK_OVERFLOW = false;
                STACK_EMPTY = false;
                stack[++top] = rand()%10;
            }
            break;
        case 'd':
            if(top == -1) {
                STACK_EMPTY = true;
            }
            else {
                STACK_EMPTY = false;
                STACK_OVERFLOW = false;
                top--;
            }
            break;
        default:
            printf("Invalid key\n");
    }
    glutPostRedisplay();
}

void drawStack() {

    glColor3f(173.0/256, 216.0/256, 230.0/256);

    float height = 20;
    float gap = 2;
    float pos = 0;
    float left = -100, right = -50;

    for(int i = 0; i < 6; i++) {
        glBegin(GL_POLYGON);

        glVertex2f(left, pos);
        glVertex2f(left, pos+height);
        glVertex2f(right, pos+height);
        glVertex2f(right, pos);

        glEnd();

        stack_text_pos[i] = pos+0.25*height;
        pos += (height + gap);
    }

    glColor3f(1, 1, 1);

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawStack();

    printText(-40, 200, "Stack Demo");
    printText(0, 100, "Press \"i\" to insert");
    printText(0, 80, "Press \"d\" to delete");
    
    if(STACK_EMPTY) {
        printText(0, -50, "STACK EMPTY");
    }
    if(STACK_OVERFLOW) {
        printText(0, -50, "STACK OVERFLOW");
    }

    for(int i = 0; i <= top; i++) {
        char num[2];
        sprintf(num, "%d", stack[i]);
        printText(-77, stack_text_pos[i], num, true);
    }

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Stack");

    srand(time(0));

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    initGL();

    glutMainLoop();
    return 0;
}