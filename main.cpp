/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.2.1/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
  //10 teapots
    for(int i=0;i<10;i++){
      glPushMatrix();
      //move (x,y) by (cos(radians of 36*i),sin(radians of 36*i))
      glTranslatef(1*cos(36*i*M_PI/180.0),1*sin(36*i*M_PI/180.0),0);
      //rotate by angle 36*i
      glRotatef(i*36, 0, 0, 1);
      glutSolidTeapot(.2);
      //reset to origin
      glPopMatrix();
    }
}

void problem2() {
  //20 steps
	for(int i=20;i>0;i--){
    //length from left to right
	  for(int j=0;j<i;j++){
      glutSolidCube(1);
	    glPushMatrix();
      //move right
	    glTranslatef(1,0,0);
	    }
	  glPopMatrix();
    //position 1 right and 0.5 up
	  glTranslatef(1,0.5,0);
	  }
}

void problem3() {
  //6 teapots
  for(int i=6;i>0;i--){
    //number of teapots in each row
      for(int j=0;j<i;j++){
        //create teapot move right 4 and loop
        glPushMatrix();
        glutSolidTeapot(1);
        glTranslatef(4,0,0);
      }
      //move to next row by go back to origin and move right 2 and up 3
      glPopMatrix();
      glTranslatef(2,3,0);
    }
}

void problem4() {
    //loop through full circle
    for (float i = 0; i < 3*M_PI; i += 0.4) {
    //first pushmatrix
    glPushMatrix();
    //rotate by i*45 degrees;
    glRotatef(i*45, 0, 0, 1);
    //i+= changes spike shape
    for (float j = 0; j < M_PI; j += 0.5) {
      //nestedpushmatrix
      glPushMatrix();
      //(x,0,0) distance from center
      glTranslatef(1,0,0);
      //rotate by i*45 degrees;
      glRotatef(j*45, 0, 0, 1);
      glutSolidCube(1);
      glPopMatrix();
    }
    glPopMatrix();
  }
  //create triangle with vertices
  glBegin(GL_TRIANGLES);
  glColor3f(1, 1, 1);
  glVertex3f(-0.25, 0, -0.25);
  glVertex3f(0.25, 0, -0.25);
  glVertex3f(0, 0.25, -0.25);
  glEnd();
  glPopMatrix();
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
