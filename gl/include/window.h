#ifndef __CENO_GL_WINDOW_H__
#define __CENO_GL_WINDOW_H__

#include <SDL2/SDL.h>
#include "../include/pixel_matrix_buf.h"
#include "../include/gl2d.h"
#include "../include/gl3d.h"

namespace CenoGL
{
	class Window{
   		private:
   		    bool running = true;

   		    SDL_Window* window = NULL;
   		    SDL_Renderer* renderer = NULL;
   		    SDL_Surface* primarySurface = NULL;

   		    int windowWidth=256;
   		    int windowHeight=256;

			char *windowName = "framework window";

			PixelMatrix *pixelMatrix;
			PixelMatrix *pixelMatrix2; //double buffer


			gl2D *gl2d;
			gl3D *gl3d;

			Mesh meshCube;
			Mat4x4 matProjection;
			Vec3D vCamera;
			Vec3D vLookDir;
			float fYaw;

			
	
   		private:

   		    // Capture SDL Events
   		    void onEvent(SDL_Event* Event);
	
   		    // Initialize our SDL game / app
   		    bool init();
	
   		    // Logic loop
   		    void update();
	
   		    // Render loop (draw)
   		    void display();
	
   		    // Free up resources
   		    void cleanUp();

			void clear();

			template<size_t size>
			void onKeyPressed(bool(&keys)[size]);

   		public:
	
   		    int run();

   		public:

		    Window();
			Window(int windowWidth, int windowHeight, const char *windowName);

   		    int GetWindowWidth();
   		    int GetWindowHeight();

			void setWindowWidth(int width){this->windowWidth = width;};
   		    void setWindowHeight(int height){this->windowHeight = height;};

			void setWindowName(char *name){this->windowName = name;};

			void initPixelMatrixBuffer();

			void setPixelMatrix(PixelMatrix *pixelMatrix){this->pixelMatrix = pixelMatrix;}

	};
};
#endif // !__CENO_GL_WINDOW_H__