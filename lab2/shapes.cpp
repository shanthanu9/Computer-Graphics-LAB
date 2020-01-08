#include <GL/glut.h>

GLfloat angle = 0.0f;

// Initialization
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set background color to black and opaque
}

// Callback when there is no other event to handle
void idle() {
    glutPostRedisplay(); // Post a repaint request to activate display()
}

// Callback for window-repaint request
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Enable Model view for translations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw triangle
    glPushMatrix();
    glTranslatef(-0.5f, 0.5f, 0.0f);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.2, -0.2);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0.0, 0.3);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(0.2, -0.2);
    glEnd();
    glPopMatrix();

    // Draw Trapezium
    glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.0f);
    glRotatef(angle, 1.0, 1.0, 0.5);
    glBegin(GL_QUADS);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(-0.3, -0.2);
        glColor3f(0.2, 0.7, 1.0);
        glVertex2f(-0.2, 0.2);
        glColor3f(0.4, 0.7, 0.5);
        glVertex2f(0.2, 0.2);
        glColor3f(0.0f, 1.0f, 0.5f);
        glVertex2f(0.3, -0.2);
    glEnd();
    glPopMatrix();

    // Draw Pentagon
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);
    glRotatef(angle, 0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(0.2, -0.2);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(-0.2, -0.2);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2f(-0.3, 0);
        glColor3f(1.0, 0.0, 1.0);
        glVertex2f(0, 0.2);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0.3, 0);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();

    angle += 1.0f;
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double-buffered mode
    glutCreateWindow("Shapes");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    initGL();
    glutMainLoop();
    return 0;
}