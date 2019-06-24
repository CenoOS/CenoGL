#include "../include/glut.h"

namespace CenoGL{
	glut::glut(PixelMatrix* pixels_buf){}
	void glut::glutCreateSDLWindow(int width,int height,const char *name){}
	void glut::glutSetSDLWindowClearColor(int color){}
	void glut::glutSetDisplayFunc(void (*display)()){}
	void glut::glutSetKeyPressedFunc(void (*keyPressed)(int key)){}
	void glut::glutSetMouseMoveFunc(void (*mouseMove)(int x,int y)){}
	void glut::glutSetMouseClickFunc(void (*mouseClick)(int key)){}
	void glut::glutSetIdleFunc(void (*update)()){}
	glut::~glut(){}
} // namespace CenoGL
