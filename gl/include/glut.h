#ifndef __CENO_GL_GRAPHICS_UTILS_H__
#define __CENO_GL_GRAPHICS_UTILS_H__

#include "../include/graphics_base_hal.h"

namespace CenoGL
{
	class glut{
		private:
			GraphicsBaseHAL *mGraphicsBaseHAL;
			PixelMatrix *pixel_matrix_buffer;
		public:
			glut(PixelMatrix* pixels_buf);

			void glutCreateSDLWindow(int width,int height,const char *name);
			void glutSetSDLWindowClearColor(int color);

			void glutSetDisplayFunc(void (*display)());
			void glutSetKeyPressedFunc(void (*keyPressed)(int key));
			void glutSetMouseMoveFunc(void (*mouseMove)(int x,int y));
			void glutSetMouseClickFunc(void (*mouseClick)(int key));
			void glutSetIdleFunc(void (*update)());

			~glut();
	};
}; // CenoGL



#endif // !__CENO_GL_GRAPHICS_UTILS_H__