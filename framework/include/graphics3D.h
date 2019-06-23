#ifndef __CENO_GL_GRAPHICS_3D_H__
#define __CENO_GL_GRAPHICS_3D_H__
#include <vector>
#include "../include/graphics_base_hal.h"

namespace CenoGL
{


	struct Vec3D{
		float x,y,z;
	};

	struct Triangle{
		Vec3D p[3];
		uint32_t color;
	};

	struct Mesh{
		std::vector<Triangle> tris;
	};

	struct Mat4x4{
		float m[4][4] = {0};
	};

	class Graphics3D{
		private:
			GraphicsBaseHAL *mGraphicsBaseHAL;
			PixelMatrix *pixel_matrix_buffer;
		public:
			Graphics3D(PixelMatrix* pixels_buf);

			void multiplyMatrixVector(Vec3D &i, Vec3D &o, Mat4x4 &m);
			uint32_t getLumColor(uint32_t color,float lum);
			~Graphics3D();
	};
}; // CenoGL
#endif //! __CENO_GL_GRAPHICS_3D_H__

