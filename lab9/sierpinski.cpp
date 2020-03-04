#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define abs(a) ((a<0)?(-a):(a))
#define sign(a) ((a>0)?1:-1)    // NOTE: sign(0) = 0

int n;

struct point {
    float x, y;
};

void initGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // gluOrtho2D( -250.0, 250.0, -150.0, 250.0 );
}

struct point *midpoint(struct point a, struct point b) {
    struct point *mid = (struct point *) malloc(sizeof(struct point));
    mid->x = (a.x+b.x)/2;
    mid->y = (a.y+b.y)/2;
    return mid;
}

void sierpinski(struct point p[3], int n) {
    if(n > 0) {
        struct point *mid[3];
        for(int i = 0; i < 3; i++) mid[i] = midpoint(p[i%3], p[(i+1)%3]);

        struct point up[3] = {p[0], *mid[0], *mid[2]}; 
        struct point right[3] = {p[1], *mid[1], *mid[0]};
        struct point left[3] = {p[2], *mid[1], *mid[2]};

        sierpinski(up, n-1);
        sierpinski(right, n-1);
        sierpinski(left, n-1);
    }
    else {
        glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 1);
        for(int i = 0; i < 3; i++) glVertex2f(p[i].x, p[i].y);
        glEnd();    
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    struct point p[3] = {{             0, 0.75}, 
                         { 0.75 / sqrt(3),   0}, 
                         {-0.75 / sqrt(3),   0}};

    sierpinski(p, n-1);
    
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sierpinski");

    if(argc == 2) {
        n = atoi(argv[1]);
        if(n <= 0) {
            printf("Value should be greater than zero\n");
            return 0;
        }
    }
    else {
        printf("usage: ./a.out n\n");
        return 1;
    }

    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}