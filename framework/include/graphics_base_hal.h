#ifndef __CENO_GL_GRAPHICS_BASE_HAL__
#define __CENO_GL_GRAPHICS_BASE_HAL__

#include "../include/pixel_matrix_buf.h"

typedef unsigned int uint32_t;

namespace CenoGL
{
	class GraphicsBaseHAL{
		private:
		public:
			GraphicsBaseHAL();
			void drawPixel(PixelMatrix *pixel_matrix_buffer,int x,int y,uint32_t color);
			~GraphicsBaseHAL();
	};
}; // CenoGL



#endif //! __CENO_GL_GRAPHICS_BASE_HAL__