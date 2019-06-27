#ifndef __CENO_GL_GRAPHICS_2D_H__
#define __CENO_GL_GRAPHICS_2D_H__

#include "../include/graphics_base_hal.h"

namespace CenoGL
{
	class gl2D{
		private:
			GraphicsBaseHAL *mGraphicsBaseHAL;
			PixelMatrix *pixel_matrix_buffer;
		public:
			gl2D(PixelMatrix* pixels_buf);
			void glFill(int x1, int y1, int x2, int y2, uint32_t c);
			void glClip(int &x, int &y);
			void glDrawLine(int x1, int y1, int x2, int y2, uint32_t c);
			void glDrawCircle(int xc, int yc, int r, uint32_t c);
			void glDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);
			void glFillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);
			void glFillCircle(int xc, int yc, int r, uint32_t c);
			~gl2D();
	};
}; // CenoGL




#endif //! __CENO_GL_GRAPHICS_2D_H__

