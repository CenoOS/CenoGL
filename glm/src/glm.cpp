#include "../include/glm.h"

namespace CenoGL
{

	Vec3D glmVectorAdd(Vec3D &v1,Vec3D &v2){
		#if NO_PARALLEL
			Vec3D vec;
			vec.x =  v1.x + v2.x;
			vec.y =  v1.y + v2.y;
			vec.z =  v1.z + v2.z;
			return vec;
		#endif
	}

	Vec3D glmVectorSub(Vec3D &v1,Vec3D &v2){
		#if NO_PARALLEL
			Vec3D vec;
			vec.x =  v1.x-v2.x;
			vec.y =  v1.y-v2.y;
			vec.z =  v1.z-v2.z;
			return vec;
		#endif
	}

	Vec3D glmVectorMul(Vec3D &v1,float k){
		#if NO_PARALLEL
			Vec3D vec;
			vec.x =  v1.x*k;
			vec.y =  v1.y*k;
			vec.z =  v1.z*k;
			return vec;
		#endif
	}
	
	Vec3D glmVectorMul(Vec3D &v1,Vec3D &v2){
		#if NO_PARALLEL
			Vec3D vec;
			vec.x =  v1.x*v2.x;
			vec.y =  v1.y*v2.y;
			vec.z =  v1.z*v2.z;
			return vec;
		#endif
	}

	Vec3D glmVectorDiv(Vec3D &v1,float k){
		#if NO_PARALLEL
			Vec3D vec;
			vec.x =  v1.x/k;
			vec.y =  v1.y/k;
			vec.z =  v1.z/k;
			return vec;
		#endif
	}
	
	Vec3D glmVectorDiv(Vec3D &v1,Vec3D &v2){
		#if NO_PARALLEL
			Vec3D vec;
			vec.x =  v1.x/v2.x;
			vec.y =  v1.y/v2.y;
			vec.z =  v1.z/v2.z;
			return vec;
		#endif
	}

	float glmVectorDotProduct(Vec3D &v1,Vec3D &v2){
		#if NO_PARALLEL
			return v1.x*v2.x + v1.y*v2.y+v1.z*v2.z;
		#endif
	}

	float glmVectorLength(Vec3D &v){
		#if NO_PARALLEL
			return sqrtf(glmVectorDotProduct(v,v));
		#endif
	}

	Vec3D glmVectorNormalise(Vec3D &v1){
		#if NO_PARALLEL
			float l = glmVectorLength(v1);
			Vec3D vec;
			vec.x =  v1.x/l;
			vec.y =  v1.y/l;
			vec.z =  v1.z/l;
			return vec;
		#endif
	}

	Vec3D glmVectorCrossProduct(Vec3D &v1,Vec3D &v2){
		#if NO_PARALLEL
			Vec3D v;
			v.x = v1.y * v2.z - v1.z * v2.y;
			v.y = v1.z * v2.x - v1.x * v2.z;
			v.z = v1.x * v2.y - v1.y * v2.x;
			return v;
		#endif
	}

	Vec3D glmMatrixMultiplyVector(Mat4x4 &m, Vec3D &i){
		#if NO_PARALLEL
			Vec3D v;
			v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
			v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
			v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
			v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
			return v;
		#endif
	}

	Mat4x4 glmMatrixMultiplyMatrix(Mat4x4 &m1, Mat4x4 &m2){
		#if NO_PARALLEL
			Mat4x4 matrix;
			for(int c = 0; c < 4; c++){
				for(int r = 0; r < 4; r++){
					matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
				}
			}
			return matrix;
		#endif
	}

	Mat4x4 glmMatrixQuickInverse(Mat4x4 &m){
		#if NO_PARALLEL
			Mat4x4 matrix;
			matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
			matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
			matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
			matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
			matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
			matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
			matrix.m[3][3] = 1.0f;
			return matrix;
		#endif
	}
};
