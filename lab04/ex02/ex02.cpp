#include <Math.h>
#include <iostream>
#include "..\..\Dependencies\glew\glew.h"
#include "..\..\Dependencies\freeglut\freeglut.h"


const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;

const char LEFT = 0;
const char RIGHT = 1;

char legStates[2];
char armStates[2];

float legAngles[2];
float armAngles[2];

float angle;

const char MOVE_LEFT = 0;
const char MOVE_RIGHT = 1;
const char MOVE_UP = 3;
const char MOVE_DOWN = 4;

const int TURN_LEFT = -90;
const int TURN_RIGHT = 90;
const int TURN_UP = 180;
const int TURN_DOWN = 0;

const int GROUND_SIZE = 200;
const float FLOOR_HEIGHT = -2;
const int CHECK_SIZE = 5;

int moveDirection;
float moveX;
float moveZ;
float theta;
float y;
float dTheta;
float dy;

void DrawGround();
void SettingCamera(float theta, float y);
void Keyboard(unsigned char key, int, int);
void Special(int key, int, int);

void DrawGround()
{
	int x, z;
	int counter = 0;
	for (x = -GROUND_SIZE; x < GROUND_SIZE; x += CHECK_SIZE)
	{
		for (z = -GROUND_SIZE; z < GROUND_SIZE; z += CHECK_SIZE)
		{
			if (counter % 2 == 0)
				glColor3f(0.2, 0.2, 1.0);
			else
				glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_QUADS);
			glNormal3d(0, 1, 0);
			glVertex3f(x, FLOOR_HEIGHT, z);
			glVertex3f(x, FLOOR_HEIGHT, z + CHECK_SIZE);
			glVertex3f(x + CHECK_SIZE, FLOOR_HEIGHT, z + CHECK_SIZE);
			glVertex3f(x + CHECK_SIZE, FLOOR_HEIGHT, z);
			glEnd();
			counter++;
		}
		counter++;
	}
}

void SettingCamera(float theta, float y)
{
	gluLookAt(50 * sin(theta), y, 50 * cos(theta),
		0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void Keyboard(unsigned char key, int, int)
{
	switch (key)
	{
	case 'a': theta -= dTheta;
		break;
	case 'd': theta += dTheta;
		break;
	case 'w': y += dy;
		break;
	case 's': if (y > dy) y -= dy;
		break;
	}
	glutPostRedisplay();
}

void Special(int key, int, int)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		moveDirection = MOVE_LEFT;
		angle = TURN_LEFT;
		break;
	case GLUT_KEY_RIGHT:
		moveDirection = MOVE_RIGHT;
		angle = TURN_RIGHT;
		break;
	case GLUT_KEY_UP:
		moveDirection = MOVE_UP;
		angle = TURN_UP;
		break;
	case GLUT_KEY_DOWN:
		moveDirection = MOVE_DOWN;
		angle = TURN_DOWN;
		break;
	}
	glutPostRedisplay();
}
void DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	glBegin(GL_QUADS);

	glNormal3d(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glNormal3d(0, 0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);

	glNormal3d(1, 0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);

	glNormal3d(-1, 0, 0);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glNormal3d(0, -1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glNormal3d(0, 0, -1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);

	glEnd();
	glPopMatrix();
}
void DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(xPos, yPos, zPos);
	glScalef(1.0f, 4.0f, 1.0f);
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}
void DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(xPos, yPos, zPos);
	glScalef(2.0f, 2.0f, 2.0f);
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(xPos, yPos, zPos);
	glScalef(3.0f, 5.0f, 2.0f);
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(xPos, yPos, zPos);
	glScalef(1.0f, 5.0f, 1.0f);
	DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}
void DrawRobot(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);;
	DrawHead(1.0f, 2.0f, 0.0f);
	DrawTorso(1.5f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);;
	glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
	DrawArm(2.5f, 0.0f, -0.5f);
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);;
	glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
	DrawArm(-1.5f, 0.0f, -0.5f);
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);;
	glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
	DrawArm(-0.5f, -5.0f, -0.5f);
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);;
	glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
	DrawArm(1.5f, -5.0f, -0.5f);
	glPushMatrix();
	glPopMatrix();
}

void Prepare()
{
	for (char side = 0; side < 2; side++)
	{
		if (armStates[side] == FORWARD_STATE)
			armAngles[side] += 0.1f;
		else
		{
			armAngles[side] -= 0.1f;
		}

		if (armAngles[side] >= 15.0f)
			armStates[side] = BACKWARD_STATE;
		else if (armAngles[side] <= -15.0f)
		{
			armStates[side] = FORWARD_STATE;
		}

		if (legStates[side] == FORWARD_STATE)
			legAngles[side] += 0.1f;
		else
		{
			legAngles[side] -= 0.1f;
		}

		if (legAngles[side] >= 15.0f)
			legStates[side] = BACKWARD_STATE;
		else if (armAngles[side] <= -15.0f)
		{
			legStates[side] = FORWARD_STATE;
		}

		switch (moveDirection) {
		case MOVE_LEFT:
			moveX = moveX - 0.015f;
			break;
		case MOVE_RIGHT:
			moveX = moveX + 0.015f;
			break;
		case MOVE_UP:
			moveZ = moveZ - 0.015f;
			break;
		case MOVE_DOWN:
			moveZ = moveZ + 0.015f;
			break;
		}
	}
}

void Display()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	SettingCamera(theta, y);

	glPushMatrix();
	glTranslatef(moveX, 8.0f, moveZ);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	Prepare();
	DrawRobot(0.0f, 0.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	DrawGround();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void Init()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos[] = { 25.0f, 25.0f, 25.0f, 0.0f };
	GLfloat spotDir[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;
	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;
	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;

	moveDirection = MOVE_LEFT;
	angle = TURN_LEFT;
	moveX = 0.0f;
	moveZ = 0.0f;

	theta = 0.0f;
	y = 5.0f;
	dTheta = 0.04f;
	dy = 1.0f;
}

void Reshape(int Width, int Height)
{
	glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)Width / (GLfloat)Height, 1.0, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void Idle()
{
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Robot_02");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutSpecialFunc(Special);
	glutKeyboardFunc(Keyboard);
	Init();
	glutMainLoop();
	return 0;
}
