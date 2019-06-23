#include <stdint.h>
#include <cmath>
#include "../include/graphics3D.h"

namespace CenoGL{

	Graphics3D::Graphics3D(PixelMatrix* pixels_buf){
		this->mGraphicsBaseHAL = new GraphicsBaseHAL();
		this->pixel_matrix_buffer = pixels_buf;
	}

	void Graphics3D::multiplyMatrixVector(Vec3D &i, Vec3D &o, Mat4x4 &m){
		o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.x /= w; o.y /= w; o.z /= w;
		}
	}

	uint32_t Graphics3D::getLumColor(uint32_t color,float lum){
		uint32_t r = (uint32_t)(((color >> 24) & 0xFF) * lum);
		uint32_t g = (uint32_t)(((color >> 16) & 0xFF) * lum);
		uint32_t b = (uint32_t)(((color >> 8) & 0xFF) * lum);
		uint32_t a = (uint32_t)(((color >> 0) & 0xFF) * lum);

		return (uint32_t)(r << 24 | g << 16 | b << 8 | a << 0);
	}

	Graphics3D::~Graphics3D(){
	}



}; // CenoGL