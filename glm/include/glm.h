#ifndef __CENO_GL_GRAPHICS_3D_MATH_H__
#define __CENO_GL_GRAPHICS_3D_MATH_H__

#include <math.h>

namespace CenoGL
{
	struct Vec3D{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 1;
	};

	struct Mat4x4{
		float m[4][4] = {0};
	};


	Vec3D glmVectorAdd(Vec3D &v1,Vec3D &v2);
	Vec3D glmVectorSub(Vec3D &v1,Vec3D &v2);
	Vec3D glmVectorMul(Vec3D &v1,float k);
	Vec3D glmVectorMul(Vec3D &v1,Vec3D &v2);
	Vec3D glmVectorDiv(Vec3D &v1,float k);
	Vec3D glmVectorDiv(Vec3D &v1,Vec3D &v2);
	float glmVectorDotProduct(Vec3D &v1,Vec3D &v2);
	float glmVectorLength(Vec3D &v);
	Vec3D glmVectorNormalise(Vec3D &v1);
	Vec3D glmVectorCrossProduct(Vec3D &v1,Vec3D &v2);
	Vec3D  glmMatrixMultiplyVector(Mat4x4 &m, Vec3D &i);
	Mat4x4 glmMatrixMultiplyMatrix(Mat4x4 &m1, Mat4x4 &m2);

	Mat4x4 glmMatrixQuickInverse(Mat4x4 &m);

};


#endif // ! __CENO_GL_GRAPHICS_3D_MATH_H__