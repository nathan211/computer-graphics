#include "Dependencies/freeglut/freeglut.h"
#include <Windows.h>

void drawBlock() {
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(-0.5, -0.5);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawBlock();

	glFlush();
}

void init() {
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Exam01");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
	return 0;
}