#include <stdint.h>
#include <cmath>
#include "../include/graphics3D.h"

namespace CenoGL{

	Graphics3D::Graphics3D(PixelMatrix* pixels_buf){
		this->mGraphicsBaseHAL = new GraphicsBaseHAL();
		this->pixel_matrix_buffer = pixels_buf;
	}

	Vec3D Graphics3D::glVectorAdd(Vec3D &v1,Vec3D &v2){
		return {v1.x+v2.x, v1.y+v2.y, v1.y+v2.y};
	}
	Vec3D Graphics3D::glVectorSub(Vec3D &v1,Vec3D &v2){}
	Vec3D Graphics3D::glVectorMul(Vec3D &v1,float k){}
	Vec3D Graphics3D::glVectorDiv(Vec3D &v1,float k){}
	float Graphics3D::glVectorDotProduct(Vec3D &v1,Vec3D &v2){}
	float Graphics3D::glVectorLength(Vec3D &v1,Vec3D &v2){}
	Vec3D Graphics3D::glVectorNormalise(Vec3D &v1){}
	Vec3D Graphics3D::glVectorCrossProduct(Vec3D &v1,Vec3D &v2){}

	Vec3D Graphics3D::glMatrixMultiplyVector(Mat4x4 &m, Vec3D &i){
		o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	}
	Vec3D Graphics3D::glMatrixMultiplyMatrix(Mat4x4 &m1, Mat4x4 &m2){}
	Mat4x4 Graphics3D::glMatrixMakeIdentity(){}
	Mat4x4 Graphics3D::glMatrixMakeRotationX(float angle){}
	Mat4x4 Graphics3D::glMatrixMakeRotationY(float angle){}
	Mat4x4 Graphics3D::glMatrixMakeRotationZ(float angle){}
	Mat4x4 Graphics3D::glMatrixMakeTranslation(float x, float y, float z){}
	Mat4x4 Graphics3D::glMatrixMakeProjection(float fovDegree, float aspectRatio, float near, float far){}

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