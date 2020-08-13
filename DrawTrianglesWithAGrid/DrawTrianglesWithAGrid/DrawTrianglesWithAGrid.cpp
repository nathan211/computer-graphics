//#include "..\..\Dependencies\glew\glew.h"
#include "..\..\Dependencies\freeglut\freeglut.h"
#include <Windows.h>

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

void drawRedTriangle(float x, float y) {
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y); 
	glVertex2f(x + 8, y);
	glVertex2f(x + 8, y + 3);
	glEnd();
}

void drawBlueTriangle(float x, float y) {
	glColor3f(0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + 5, y);
	glVertex2f(x + 5, y + 2);
	glEnd();
}

void drawGreenBlock(float x, float y) {
	glColor3f(0, 1, 0);

	glBegin(GL_QUADS);

	glVertex2f(x, y);
	glVertex2f(x + 2, y);
	glVertex2f(x + 2, y + 1);
	glVertex2f(x, y + 1);

	glVertex2f(x, y + 1);
	glVertex2f(x + 5, y + 1);
	glVertex2f(x + 5, y + 2);
	glVertex2f(x, y + 2);

	glEnd();
}

void drawLightBlueBlock(float x, float y) {
	glColor3f(0, 1, 1);

	glBegin(GL_QUADS);

	glVertex2f(x, y);
	glVertex2f(x + 5, y);
	glVertex2f(x + 5, y + 1);
	glVertex2f(x, y + 1);

	glVertex2f(x + 2, y + 1);
	glVertex2f(x + 5, y + 1);
	glVertex2f(x + 5, y + 2);
	glVertex2f(x + 2, y + 2);

	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawRedTriangle(1, 9);
	drawRedTriangle(6, 3);

	drawBlueTriangle(1, 1);
	drawBlueTriangle(9, 12);

	drawGreenBlock(6, 1);
	drawGreenBlock(9, 10);

	drawLightBlueBlock(9, 1);
	drawLightBlueBlock(9, 9);

	drawGrid();
	
	glFlush();
}

void init() {
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 15, 0, 15, -1.0, 1.0);
}

int main(int argc, char** argv){
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
