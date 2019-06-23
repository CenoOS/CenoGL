#ifndef __CENO_GL_GRAPHICS_2D_H__
#define __CENO_GL_GRAPHICS_2D_H__

#include "../include/graphics_base_hal.h"

namespace CenoGL
{
	class Graphics2D{
		private:
			GraphicsBaseHAL *mGraphicsBaseHAL;
			PixelMatrix *pixel_matrix_buffer;
		public:
			Graphics2D(PixelMatrix* pixels_buf);
			void fill(int x1, int y1, int x2, int y2, uint32_t c);
			void clip(int &x, int &y);
			void drawLine(int x1, int y1, int x2, int y2, uint32_t c);
			void drawCircle(int xc, int yc, int r, uint32_t c);
			void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);
			void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);
			void fillCircle(int xc, int yc, int r, uint32_t c);
			~Graphics2D();
	};
}; // CenoGL




#endif //! __CENO_GL_GRAPHICS_2D_H__

