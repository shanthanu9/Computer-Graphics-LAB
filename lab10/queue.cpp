#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0

float queue_text_pos[6];
int front = -1, rear = -1, n = 0;
bool QUEUE_FULL = false, QUEUE_EMPTY = true;
bool QUEUE_INSERT = false, QUEUE_DELETE = false;
int queue[6];

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
            QUEUE_EMPTY = false;
            QUEUE_FULL = false;
            QUEUE_INSERT = false;
            QUEUE_DELETE = false;
            if(n == 6) {
                QUEUE_FULL = true;
            }
            else {
                QUEUE_INSERT = true;
                if(front == -1 && rear == -1) {
                    rear = front = 0;
                }
                else {
                    rear = (rear+1)%6;
                }
                n++;
                queue[rear] = rand()%10;
            }
            break;
        case 'd':
            QUEUE_EMPTY = false;
            QUEUE_FULL = false;
            QUEUE_INSERT = false;
            QUEUE_DELETE = false;
            if(n == 0) {
                QUEUE_EMPTY = true;
            }
            else {
                QUEUE_DELETE = true;
                front = (front+1)%6;
                n--;
                if(n == 0) {
                    front = rear = -1;
                }
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

        queue_text_pos[i] = pos+0.25*height;
        pos += (height + gap);
    }

    glColor3f(1, 1, 1);

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawStack();

    printText(-40, 200, "Queue Demo");
    printText(0, 100, "Press \"i\" to insert");
    printText(0, 80, "Press \"d\" to delete");

    if(QUEUE_EMPTY) {
        printText(0, -50, "QUEUE EMPTY");
    }
    if(QUEUE_FULL) {
        printText(0, -50, "QUEUE FULL");
    }
    if(QUEUE_INSERT) {
        printText(0, -50, "INSERT ELEMENT");
    }
    if(QUEUE_DELETE) {
        printText(0, -50, "DELETE ELEMENT");
    }

    if(front != -1) {
        printText(-120, queue_text_pos[front], "->");
    }
    if(rear != -1) {
        printText(-120, queue_text_pos[rear], "->");
    }

    for(int i = 0; i < n; i++) {
        int j = (front+i)%6;
        char num[2];
        sprintf(num, "%d", queue[j]);
        printText(-77, queue_text_pos[j], num, true);
    }

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Queue");

    srand(time(0));

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    initGL();

    glutMainLoop();
    return 0;
}