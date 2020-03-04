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

struct point d[100];

void disect(struct point a, struct point b, int n) {

    for(int i = 1; i < n; i++) {
        d[i].x = a.x + (b.x-a.x)*i/(n*1.0);
        d[i].y = a.y + (b.y-a.y)*i/(n*1.0);
    }
}

void sierpinski(struct point p[4], int n) {
    if(n > 0) {
        
        struct point sub[4][4];
        struct point edges [4][2];

        disect(p[0], p[1], 3);
        edges[1][1] = d[1];
        edges[2][1] = d[2];

        edges[0][1] = p[0];
        edges[3][1] = p[1];

        disect(p[3], p[2], 3);
        edges[1][0] = d[1];
        edges[2][0] = d[2];

        edges[0][0] = p[3];
        edges[3][0] = p[2];

        for(int i = 0; i < 4; i++) {
            disect(edges[i][0], edges[i][1], 3);
            sub[i][0] = edges[i][0];
            sub[i][1] = d[1];
            sub[i][2] = d[2];
            sub[i][3] = edges[i][1];
        }

        int count = 0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(count != 4) {
                    // printf("%d %d\n", i, j);
                    struct point sq[4] = {sub[i][j], sub[i+1][j], sub[i+1][j+1], sub[i][j+1]};
                    sierpinski(sq, n-1);
                }
                count++;
            }
        }

    }
    else {
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        for(int i = 0; i < 4; i++) glVertex2f(p[i].x, p[i].y);
        glEnd();    
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    struct point p[4] = {{ 0.5,  0.5},
                         { 0.5, -0.5},
                         {-0.5, -0.5},
                         {-0.5,  0.5}};

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