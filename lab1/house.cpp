#include <GL/glut.h>
// Initialization
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set background color to black and opaque
}

void drawRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    height /= 2;
    width  /= 2;
    glVertex2f(x-width, y-height);
    glVertex2f(x-width, y+height);
    glVertex2f(x+width, y+height);
    glVertex2f(x+width, y-height);
}

void drawSquare(GLfloat x, GLfloat y, GLfloat side) {
    drawRectangle(x, y, side, side);
}

void drawMountain(GLfloat x, GLfloat y, GLfloat side) {
    glVertex2f(x-side, y);
    glVertex2f(x, y+side);
    glVertex2f(x+side, y);
}

// Call back handler for window repaint request
void display() {
    glClear(GL_COLOR_BUFFER_BIT);           // Clear the color buffer

    // Draw House body
    glBegin(GL_QUADS);
        // Outline
        #define HOUSE_SIDE 1.0f
        glColor3f(1.00, 0.83, 0.00);
        drawSquare(0, 0, HOUSE_SIDE);

        // Windows
        #define WIN_SIDE 0.2f
        glColor3f(0.54, 0.81, 0.94);
        drawSquare(0.25, 0.25, WIN_SIDE);
        drawSquare(-0.25, 0.25, WIN_SIDE);

        // Door
        #define DOOR_WIDTH 0.4
        #define DOOR_HEIGHT 0.5
        glColor3f(0.40,0.26,0.13);
        drawRectangle(0, -0.25, DOOR_WIDTH, DOOR_HEIGHT);

    glEnd();

    // Draw House top
    glBegin(GL_TRIANGLES);
        glColor3f(0.59f, 0.29f, 0.0f);
        glVertex2f(-0.6f, 0.5f);
        glVertex2f(0.0f, 0.75f);
        glVertex2f(0.6f,  0.5f);
    glEnd();

    // Draw house steps
    glBegin(GL_QUADS);
        #define STEP_HEIGHT 0.05f
        glColor3f(1.0,0.00,0.00);
        drawRectangle(0, -0.55, 0.6, STEP_HEIGHT);
        drawRectangle(0, -0.60, 0.5, STEP_HEIGHT);
        drawRectangle(0, -0.65, 0.4, STEP_HEIGHT);
    glEnd();

    // Mountains
    glBegin(GL_TRIANGLES);
        glColor3f(0.59,0.44,0.09);
        for(float x = -0.8; x <= 0.8; x += 0.2)
            drawMountain(x, 0.8, 0.1);
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