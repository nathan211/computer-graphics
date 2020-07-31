#include <math.h>
#include "..\lab01\Dependencies\glew\glew.h"
#include "..\lab01\Dependencies\freeglut\freeglut.h"


#define STEPS 40
#define MAX_STARS 300
#define PI 3.14159265358979323846

const int screenWidth = 640;
const int screenHeight = 480;

typedef struct star {
	GLint x, y;
	GLint radius;
	GLint velocity;
	GLfloat intensity;
} STAR;

STAR sky[MAX_STARS];

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0); // black
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

void skyInit() {
	for (int i = 0; i < MAX_STARS; i++) {
		sky[i].x = rand() % screenWidth;
		sky[i].y = rand() % screenHeight;
		sky[i].radius = 1 + rand() % 3;
		sky[i].intensity = sky[i].radius / 3.0f;
		sky[i].velocity = sky[i].radius * 2 + rand() % 3;
	}
}

void skyDraw() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < MAX_STARS; i++) {
		glColor3f(sky[i].intensity, sky[i].intensity, sky[i].intensity);
		glCircle(sky[i].x, sky[i].y, sky[i].radius);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
	skyDraw();
	glPopMatrix();
	glutSwapBuffers();
}

void update() {
	for (int i = 0; i < MAX_STARS; i++) {
		sky[i].x += sky[i].velocity;
		if (sky[i].x >= screenWidth) {
			sky[i].x = 0;
			sky[i].y = rand() % screenHeight;
			sky[i].radius = 1 + rand() % 3;
			sky[i].intensity = sky[i].radius / 3.0f;
			sky[i].velocity = sky[i].radius * 2 + rand() % 3;
		}
	}

	Sleep(50);
	glutPostRedisplay();
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
	skyInit();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	glutMainLoop();
	return 0;
}
