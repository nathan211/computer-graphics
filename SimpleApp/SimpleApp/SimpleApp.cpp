#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"


void MyDisplay(){
    glClearColor(255 / 255, 0, 255 / 255, 1);
    glColor3f(1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);

    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);

    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple");
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
