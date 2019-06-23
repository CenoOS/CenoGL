#include <stdint.h>
#include <cmath>
#include "../include/graphics3D.h"

namespace CenoGL{

	Graphics3D::Graphics3D(PixelMatrix* pixels_buf){
		this->mGraphicsBaseHAL = new GraphicsBaseHAL();
		this->pixel_matrix_buffer = pixels_buf;
	}

	Vec3D Graphics3D::glVectorAdd(Vec3D &v1,Vec3D &v2){
		Vec3D vec;
		vec.x =  v1.x+v2.x;
		vec.y =  v1.y+v2.y;
		vec.z = v1.z + v2.z;
		return vec;
	}

	Vec3D Graphics3D::glVectorSub(Vec3D &v1,Vec3D &v2){
		Vec3D vec;
		vec.x =  v1.x-v2.x;
		vec.y =  v1.y-v2.y;
		vec.z =  v1.z-v2.z;
		return vec;
	}

	Vec3D Graphics3D::glVectorMul(Vec3D &v1,float k){
		Vec3D vec;
		vec.x =  v1.x*k;
		vec.y =  v1.y*k;
		vec.z =  v1.z*k;
		return vec;
	}

	Vec3D Graphics3D::glVectorDiv(Vec3D &v1,float k){
		Vec3D vec;
		vec.x =  v1.x/k;
		vec.y =  v1.y/k;
		vec.z =  v1.z/k;
		return vec;
	}

	float Graphics3D::glVectorDotProduct(Vec3D &v1,Vec3D &v2){
		return v1.x*v2.x + v1.y*v2.y+v1.z*v2.z;
	}

	float Graphics3D::glVectorLength(Vec3D &v){
		return sqrtf(this->glVectorDotProduct(v,v));
	}

	Vec3D Graphics3D::glVectorNormalise(Vec3D &v1){
		float l = glVectorLength(v1);
		Vec3D vec;
		vec.x =  v1.x/l;
		vec.y =  v1.y/l;
		vec.z =  v1.z/l;
		return vec;
	}

	Vec3D Graphics3D::glVectorCrossProduct(Vec3D &v1,Vec3D &v2){
		Vec3D v;
		v.x = v1.y * v2.z - v1.z * v2.y;
		v.y = v1.z * v2.x - v1.x * v2.z;
		v.z = v1.x * v2.y - v1.y * v2.x;
		return v;
	}

	Vec3D Graphics3D::glMatrixMultiplyVector(Mat4x4 &m, Vec3D &i){
		Vec3D v;
		v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
		v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
		v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
		v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
		return v;
	}

	Mat4x4 Graphics3D::glMatrixMultiplyMatrix(Mat4x4 &m1, Mat4x4 &m2){
		Mat4x4 matrix;
		for(int c = 0; c < 4; c++){
			for(int r = 0; r < 4; r++){
				matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
			}
		}
		return matrix;
	}

	Mat4x4 Graphics3D::glMatrixMakeIdentity(){
		Mat4x4 mat;
		mat.m[0][0] = 1.0f;
		mat.m[1][1] = 1.0f;
		mat.m[2][2] = 1.0f;
		mat.m[3][3] = 1.0f;
		return mat;
	}

	Mat4x4 Graphics3D::glMatrixMakeRotationX(float angle){
		Mat4x4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = cosf(angle);
		matrix.m[1][2] = sinf(angle);
		matrix.m[2][1] = -sinf(angle);
		matrix.m[2][2] = cosf(angle);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Mat4x4 Graphics3D::glMatrixMakeRotationY(float angle){
		Mat4x4 matrix;
		matrix.m[0][0] = cosf(angle);
		matrix.m[0][2] = sinf(angle);
		matrix.m[2][0] = -sinf(angle);
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = cosf(angle);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Mat4x4 Graphics3D::glMatrixMakeRotationZ(float angle){
		Mat4x4 matrix;
		matrix.m[0][0] = cosf(angle);
		matrix.m[0][1] = sinf(angle);
		matrix.m[1][0] = -sinf(angle);
		matrix.m[1][1] = cosf(angle);
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Mat4x4 Graphics3D::glMatrixMakeTranslation(float x, float y, float z){
		Mat4x4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		matrix.m[3][0] = x;
		matrix.m[3][1] = y;
		matrix.m[3][2] = z;
		return matrix;
	}

	Mat4x4 Graphics3D::glMatrixMakeProjection(float fovDegree, float aspectRatio, float near, float far){
		float fFovRad = 1.0f / tanf(fovDegree * 0.5f / 180.0f * 3.14159f);
		Mat4x4 matrix;
		matrix.m[0][0] = aspectRatio * fFovRad;
		matrix.m[1][1] = fFovRad;
		matrix.m[2][2] = far / (far - near);
		matrix.m[3][2] = (-far * near) / (far - near);
		matrix.m[2][3] = 1.0f;
		matrix.m[3][3] = 0.0f;
		return matrix;
	}

	Mat4x4 Graphics3D::glMatrixPointAt(Vec3D &pos,Vec3D &target,Vec3D &up){
		// caculate new forward direction
		Vec3D newForward = this->glVectorSub(target,pos);
		newForward = this->glVectorNormalise(newForward);

		// caculate new up direction
		Vec3D a = this->glVectorMul(newForward,this->glVectorDotProduct(up,newForward));
		Vec3D newUp = this->glVectorSub(up,a);
		newUp = this->glVectorNormalise(newUp);

		// New Right direction is easy, its just cross product
		Vec3D newRight = this->glVectorCrossProduct(newUp, newForward);

		// Construct Dimensioning and Translation Matrix	
		Mat4x4 matrix;
		matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	 atrix.m[0][2] = newRight.z;	 matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = newUp.x;		 matrix.m[1][1] = newUp.y;		   matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = pos.x;			  matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			  matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Mat4x4 Graphics3D::glMatrixQuickInverse(Mat4x4 &m){
		Mat4x4 matrix;
		matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
		matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
		matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
		matrix.m[3][3] = 1.0f;
		return matrix;
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