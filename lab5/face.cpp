#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INTERVAL 0.01
#define XMAX 300
#define YMAX 300
#define INIT_SIZE 10

const float PI = 3.14159265;


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

void drawSmile(float cx, float cy, float r, float b_a, float e_a) {
    float x = rotatex(b_a, r, 0);
    float y = rotatey(b_a, r, 0);
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glBegin(GL_POINTS);
        float tempx, tempy;
        float factor = 0.1;
        for(float angle = b_a; angle <= e_a; angle += factor) {
            // printxy(x, y);
            glVertex2f(x, y);
            tempx = rotatex(factor, x, y);
            tempy = rotatey(factor, x, y);
            x = tempx; y = tempy;
        }
    glEnd();
    glPopMatrix();
}

void idle() {
    glutPostRedisplay();
}

bool rotate_clock = false;
bool rotate_anti = false;
bool move_left = false;
bool move_right = false;

float angle = 0;
float tx = 0;
float scale = 1;

void reset() {
    angle = 0;
    rotate_clock = false;
    rotate_anti = false;
    move_left = false;
    move_right = false;
}

void keyboard(unsigned char key, int x, int y) {
    printf("key: %c\n", key);
    switch(key) {
        case 'a':
            reset();
            rotate_clock = true; 
            break;
        case 'b':
            reset();
            rotate_anti = true;
            break;
        case 'c':
            reset();
            scale += 0.1;
            break;
        case 'd':
            reset();
            scale -= 0.1;
            break;
        case 'e':
            reset();
            tx++;
            move_right = true;
            break;
        case 'f':
            reset();
            tx--;
            move_left = true;
            break;
        case 'r':
            reset();
            scale = 1;
            tx = 0;
            break;
        case 'x':
            exit(0);
    }
}

const float FACE_RADIUS = 150;
const float NOSE_RADIUS = 0.05 * FACE_RADIUS;
const float SMILE_RADIUS = 0.6 * FACE_RADIUS;
const float EYE_RADIUS = 0.15 * FACE_RADIUS;
const float EYEBALL_RADIUS = 0.05 * FACE_RADIUS;

const float EYE_X = 0.4 * FACE_RADIUS;
const float EYE_Y = 0.5 * FACE_RADIUS;
const float EYEBALL_DIST = 0.2 * EYE_RADIUS;

const float EYEBALL_X = 0;
const float EYEBALL_Y = - 2.0 / 3.0 * EYE_RADIUS;

void display() {
    
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(tx, 0, 0);
    glScalef(scale, scale, 0);

    // Face outline
    drawCircle(0, 0, FACE_RADIUS);

    // Nose
    drawCircle(0, 0, NOSE_RADIUS);

    // Smile
    drawSmile(0, 0, SMILE_RADIUS, 210, 330);

    // Eyes outline
    drawCircle(EYE_X, EYE_Y, EYE_RADIUS);
    drawCircle(-EYE_X, EYE_Y,EYE_RADIUS);

    // Eye balls
    glPushMatrix();
        glTranslatef(EYE_X, EYE_Y, 0);
        glRotatef(angle, 0, 0, 1);
        drawCircle(EYEBALL_X, EYEBALL_Y, EYEBALL_RADIUS);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-EYE_X, EYE_Y, 0);
        glRotatef(angle, 0, 0, 1);
        drawCircle(EYEBALL_X, EYEBALL_Y, EYEBALL_RADIUS);
    glPopMatrix();
    // drawCircle(-EYEBALL_X, EYEBALL_Y, EYEBALL_RADIUS);

    glPopMatrix();

    if(rotate_clock) {
        angle -= 0.1;
    }
    if(rotate_anti) {
        angle += 0.1;
    }

    // if(move_right) tx += 0.01;
    // if(move_left) tx -= 0.01;

    if(angle > 360) angle -= 360;

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(2*XMAX, 2*YMAX);
    glutCreateWindow("Smily Face");

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    initGL();
    glutMainLoop();
    return 0;
}