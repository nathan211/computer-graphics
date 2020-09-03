#include "..\..\Dependencies\freeglut\freeglut.h"
#include <Windows.h>
#include <Math.h>

#define PI 3.1415926

float RVenus = 2.5;
float REarth = RVenus * 149600 / 108200;

void drawCircle(float x0, float y0, float R, int n = 40) {
	float x, y;
	float angleInc = 2 * PI / n;
	float angle;

	glBegin(GL_LINE_LOOP);
	angle = 0;
	x = R * cos(angle);
	y = R * sin(angle);
	glVertex2f(x, y);
	for (int i = 1; i < n; i++) {
		angle += angleInc;
		x = R * cos(angle);
		y = R * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawCircle(0, 0, RVenus);
	drawCircle(0, 0, REarth);

	float angleEarthInc = 4;
	float factor = 365.25636 / 224.7008;
	float angleVenusInc = factor * angleEarthInc;
	float xEarth, yEarth;
	float xVenus, yVenus;
	float angleEarth = 90, angleVenus = 90;

	glBegin(GL_LINES);
	for (int i = 0; i <= (360.0 / angleEarthInc) * 10; i++) {
		angleEarth -= angleEarthInc;
		angleVenus -= angleVenusInc;
		xEarth = REarth * cos(angleEarth * PI / 180);
		yEarth = REarth * sin(angleEarth * PI / 180);
		xVenus = RVenus * cos(angleVenus * PI / 180);
		yVenus = RVenus * sin(angleVenus * PI / 180);
		glVertex2f(xEarth, yEarth);
		glVertex2f(xVenus, yVenus);
	}
	glEnd();
	glFlush();
}

void init() {
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.5, 4.5, -4.5, 4.5, -1.0, 1.0);
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