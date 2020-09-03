#include "..\..\Dependencies\freeglut\freeglut.h"
#include <math.h>

#define PI 3.1159265358
#define ARCDIV 19
#define LINEDIV 16

struct Point2D {
	float x, y;
};

Point2D circleArr[ARCDIV * 5];
Point2D arcArr[5][ARCDIV];
Point2D lineArr[5][ARCDIV + 1];

float R = 4;

void drawPoint(Point2D p) {
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
}

void drawLine(Point2D p1, Point2D p2) {
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
}

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

void calculateData() {
	for (int i = 0; i < ARCDIV * 5; i++) {
		circleArr[i].x = R * cos(PI / 2 + i * 2 * PI / (ARCDIV * 5));
		circleArr[i].y = R * sin(PI / 2 + i * 2 * PI / (ARCDIV * 5));
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < ARCDIV; j++) {
			arcArr[i][j].x = circleArr[i * ARCDIV + j].x;
			arcArr[i][j].y = circleArr[i * ARCDIV + j].y;
		}
	}

	for (int i = 0; i < 5; i++) {
		lineArr[i][0].x = 0;
		lineArr[i][0].y = 0;

		lineArr[i][LINEDIV].x = arcArr[i][0].x;
		lineArr[i][LINEDIV].y = arcArr[i][0].y;	
	}

	for (int i = 0; i < 5; i++) {
		lineArr[i][0].x = 0;
		lineArr[i][0].y = 0;

		lineArr[i][LINEDIV].x = arcArr[i][0].x;
		lineArr[i][LINEDIV].y = arcArr[i][0].y;
	}

	for (int i = 0; i < 5; i++) {
		float delX = (lineArr[i][LINEDIV].x - lineArr[i][0].x) / LINEDIV;
		float delY = (lineArr[i][LINEDIV].y - lineArr[i][0].y) / LINEDIV;

		for (int j = 1; j < LINEDIV; j++) {
			lineArr[i][j].x = delX * j;
			lineArr[i][j].y = delY * j;
		}
	}
}

void drawFigure(int idx1, int idx2, float R, float G, float B) {
	glColor3f(R / 255, G / 255, B / 255);
	for (int i = 0; i < 9; i++) {
		drawLine(lineArr[idx1][9 - i], lineArr[idx2][1 + i]);
	}

	for (int i = 0; i < 10; i++) {
		drawLine(lineArr[idx1][LINEDIV - i], lineArr[idx2][i + 7]);
	}

	for (int i = 0; i < ARCDIV; i++) {
		drawLine(arcArr[idx1][i], arcArr[idx2][i]);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0, 1, 1);
	drawCircle(0, 0, R, 100);

	glColor3f(0, 0, 0);

	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < ARCDIV; j++) {
			drawPoint(arcArr[i][j]);
		}
	}

	glColor3f(0, 1, 1);
	for (int i = 0; i < 5; i++) {
		drawLine(lineArr[i][0], lineArr[i][LINEDIV]);
	}

	glColor3f(0, 0, 0);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < LINEDIV; j++) {
			drawPoint(lineArr[i][j]);
		}
	}

	glLineWidth(2);
	drawFigure(0, 1, 255, 128, 0);
	drawFigure(1, 2, 0, 255, 0);
	drawFigure(2, 3, 0, 0, 255);
	drawFigure(3, 4, 255, 0, 255);
	drawFigure(4, 0, 228, 27, 98);

	glFlush();
}

void init() {
	calculateData();

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