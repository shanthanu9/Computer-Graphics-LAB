#include <GL/glut.h>

// Initialization
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set background color to black and opaque
}

// Call back handler for window repaint request
void display() {
    glClear(GL_COLOR_BUFFER_BIT);           // Clear the color buffer

    // Draw sqaure
    glBegin(GL_QUADS);
        glColor3f(1.00,0.83,0.00);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f,  0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
    glEnd();

    // Draw triangle
    glBegin(GL_TRIANGLES);
        glColor3f(0.59f, 0.29f, 0.0f);
        glVertex2f(-0.6f, 0.5f);
        glVertex2f(0.0f, 0.75f);
        glVertex2f(0.6f,  0.5f);
    glEnd();

    glFlush();                              // Render now
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("House");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}