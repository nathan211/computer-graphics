#include "..\..\Dependencies\glew\glew.h"
#include "..\..\Dependencies\freeglut\freeglut.h"


void drawGrid() {
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_LINES);
	for (int i = 0; i < 15; i++) {
		glVertex2f(i, 0);
		glVertex2f(i, 15);
	}
	for (int i = 0; i < 15; i++) {
		glVertex2f(0, i);
		glVertex2f(15, i);
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	

	drawGrid();


	glFlush();
}

void init() {
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 15, 0, 15, 0, 15);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Example");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}