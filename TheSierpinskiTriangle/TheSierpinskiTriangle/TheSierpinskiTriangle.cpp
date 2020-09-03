#include "..\Dependencies\freeglut\freeglut.h"
#include <windows.h>
#include <time.h>


void init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	glColor3f(1.0, 0.0, 0.0); 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
}

void display(void) {
	GLfloat vertices[3][2] = { {0.0, 0.0}, {25.0, 50.0}, {50.0, 0.0} }; 
	int i, j;
	GLfloat p[2] = { 7.5, 5.0 };

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (i = 0; i < 500000; i++) {
		j = rand() % 3;
		p[0] = (p[0] + vertices[j][0]) / 2.0; 
		p[1] = (p[1] + vertices[j][1]) / 2.0;
		glVertex2fv(p);
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv){	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(680, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("The Sierpinski Triangle");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
		