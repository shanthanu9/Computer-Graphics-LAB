#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0

static int window;
static int submenu_id, menu_id;
int value;

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // gluOrtho2D( -250.0, 250.0, -150.0, 250.0 );
}

void menu(int n) {
    if(n == 0) {
        glutDestroyWindow(window);
        exit(0);
    }
    else {
        value = n;
    }
    glutPostRedisplay();
}

void createMenu() {
    submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Solid Teapot", 1);
    glutAddMenuEntry("Wired Teapot", 2);
    
    glutCreateMenu(menu);
    glutAddSubMenu("Draw", submenu_id);  
    glutAddMenuEntry("Quit", 0);   
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if(value == 1) {
        glutSolidTeapot(0.5);
    }
    else if(value == 2) {
        glutWireTeapot(0.5);
    }
    
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Teapot");

    // if(argc == 2) {
    //     n = atoi(argv[1]);
    // }
    // else {
    //     printf("usage: ./a.out n\n");
    //     return 1;
    // }
    createMenu();
    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}