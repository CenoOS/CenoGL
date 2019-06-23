#ifndef __CENO_GL_GRAPHICS_3D_H__
#define __CENO_GL_GRAPHICS_3D_H__

#include "../include/graphics_base_hal.h"

namespace CenoGL
{


	struct vec3d{
		float x,y,z;
	};

	class Graphics3D{
		private:
			GraphicsBaseHAL *mGraphicsBaseHAL;
			PixelMatrix *pixel_matrix_buffer;
		public:
			Graphics3D(PixelMatrix* pixels_buf);
		
			~Graphics3D();
	};
}; // CenoGL
#endif //! __CENO_GL_GRAPHICS_3D_H__

