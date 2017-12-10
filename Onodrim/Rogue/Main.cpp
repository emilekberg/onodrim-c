#define GLEW_STATIC
#define FREEGLUT_STATIC
#include "Core.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Rogue");

	glutMainLoop();
	onodrim::Core core;
	core.Start();
	return 0;
}