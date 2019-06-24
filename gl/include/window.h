#ifndef __CENO_GL_WINDOW_H__
#define __CENO_GL_WINDOW_H__

#include <SDL2/SDL.h>
#include "../include/pixel_matrix_buf.h"
#include "../include/gl2D.h"
#include "../include/gl3D.h"

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
   		    void OnEvent(SDL_Event* Event);
	
   		    // Initialize our SDL game / app
   		    bool Init();
	
   		    // Logic loop
   		    void Update();
	
   		    // Render loop (draw)
   		    void Render();
	
   		    // Free up resources
   		    void Cleanup();

			template<size_t size>
			void OnKeyPressed(bool(&keys)[size]);

   		public:
	
   		    int Execute();

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