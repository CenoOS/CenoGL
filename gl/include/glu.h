#ifndef __CENO_GL_GRAPHICS_GLU_H__
#define __CENO_GL_GRAPHICS_GLU_H__

#include "../include/graphics_base_hal.h"

namespace CenoGL
{
	class glu{
		private:

		public:
			glu();

			void gluFillRect(int x1, int y1, int x2, int y2, uint32_t c);
			void gluDrawLine(int x1, int y1, int x2, int y2, uint32_t c);
			void gluDrawCircle(int xc, int yc, int r, uint32_t c);
			void gluDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);
			void gluFillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t c);
			void gluFillCircle(int xc, int yc, int r, uint32_t c);

			void gluWiredBox();
			void gluSolidBox();

			void gluWiredTeapot();
			void gluSolidTeapot();

			~glu();
	};
}; // CenoGL




#endif //! __CENO_GL_GRAPHICS_GLU_H__

