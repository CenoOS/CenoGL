#ifndef __CENO_GL_GRAPHICS_UTILS_H__
#define __CENO_GL_GRAPHICS_UTILS_H__

#include <SDL2/SDL.h>
#include "../include/graphics_base_hal.h"
#include "../include/gl2d.h"

namespace CenoGL
{
	class glut{
		private:
			GraphicsBaseHAL *mGraphicsBaseHAL;
			PixelMatrix *pixel_matrix_buffer;

			bool running = true;
			uint32_t backgroundColor = 0x000000FF;

   		    SDL_Window* window = NULL;
   		    SDL_Renderer* renderer = NULL;
   		    SDL_Surface* primarySurface = NULL;

   		    int windowWidth=256;
   		    int windowHeight=256;

			const char *windowName = "framework window";


			void (*show)();
			void (*keyPressed)(int key);
			void (*mouseMove)(int x,int y);
			void (*mouseClick)(int key);
			void (*idle)();

			gl2D *gl2d;

		private:
   		    void onEvent(SDL_Event* Event);
   		    bool init();
   		    void update();
   		    void display();
   		    void cleanUp();
			void clear();
			template<size_t size>
			void onKeyPressed(bool(&keys)[size]);

		public:
			glut();

			void runGL();

			int glutGetWindowWidth(){return windowWidth;};
   		    int glutGetWindowHeight(){return windowHeight;};

			void glutSetWindowWidth(int width){this->windowWidth = width;};
   		    void glutSetWindowHeight(int height){this->windowHeight = height;};
			void glutSetWindowName(char *name){this->windowName = name;};

			void glutCreateSDLWindow(int width,int height,const char *name);
			void glutSetSDLWindowClearColor(uint32_t color);

			void glutSetDisplayFunc(void (*display)());
			void glutSetKeyPressedFunc(void (*keyPressed)(int key));
			void glutSetMouseMoveFunc(void (*mouseMove)(int x,int y));
			void glutSetMouseClickFunc(void (*mouseClick)(int key));
			void glutSetIdleFunc(void (*update)());

			~glut();
	};
}; // CenoGL



#endif // !__CENO_GL_GRAPHICS_UTILS_H__