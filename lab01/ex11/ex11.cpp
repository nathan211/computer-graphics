#include <math.h>
#include "..\lab01\Dependencies\glew\glew.h"
#include "..\lab01\Dependencies\freeglut\freeglut.h"



#define PI 3.14159265358979323846;
#define STEPS 40

const int screenWidth = 640;
const int screenHeight = 480;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void glCircle(GLint x, GLint y, GLint radius) {
	GLfloat twicePi = (GLdouble)2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(x, y);
	for (int i = 0; i <= STEPS; i++) {
		glVertex2i((GLint)(x + (radius * cos(i * twicePi / STEPS)) + 0.5), (GLint)(y + (radius * sin(i * twicePi / STEPS)) + 0.5));
	}
	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	GLfloat red = 1.0f;
	GLfloat green = 1.0f;
	GLfloat blue = 1.0f;
	for (int r = 200; r > 0; r -= 30) {
		glColor3f(red, green, blue);
		glCircle(320, 240, r);
		red -= 0.1f;
		green -= 0.2f;
		blue -= 0.3f;
	}

	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}