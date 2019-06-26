#include "../include/glm.h"


#if PARALLEL_SIMD
	#include <xmmintrin.h>
#endif

namespace CenoGL
{

	Vec3D glmVectorAdd(Vec3D &v1,Vec3D &v2){
		Vec3D vec; 
		#if NO_PARALLEL
			vec.x =  v1.x + v2.x;
			vec.y =  v1.y + v2.y;
			vec.z =  v1.z + v2.z;
			
		#endif

		#if PARALLEL_SIMD
			float a[] = { v1.x, v1.y, v1.z, v1.w };
			float b[] = { v2.x, v2.y, v2.z, v2.w };
			__m128 V1 = _mm_load_ps(a);
			__m128 V2 = _mm_load_ps(b);
			__m128 result = _mm_add_ps(V1,V2);
			vec.x = result[0]; vec.y = result[1]; vec.z = result[2]; vec.w = result[3];
		#endif	
		return vec;
	}

	Vec3D glmVectorSub(Vec3D &v1,Vec3D &v2){
		Vec3D vec;
		#if NO_PARALLEL
			vec.x =  v1.x-v2.x;
			vec.y =  v1.y-v2.y;
			vec.z =  v1.z-v2.z;
		#endif

		#if PARALLEL_SIMD
			float a[] = { v1.x, v1.y, v1.z, v1.w };
			float b[] = { v2.x, v2.y, v2.z, v2.w };
			__m128 V1 = _mm_load_ps(a);
			__m128 V2 = _mm_load_ps(b);
			__m128 result = _mm_sub_ps(V1,V2);
			vec.x = result[0]; vec.y = result[1]; vec.z = result[2]; vec.w = result[3];
		#endif	
		return vec;
	}

	Vec3D glmVectorMul(Vec3D &v1,float k){
		Vec3D vec;
		#if NO_PARALLEL
			vec.x =  v1.x*k;
			vec.y =  v1.y*k;
			vec.z =  v1.z*k;
		#endif

		#if PARALLEL_SIMD
			float a[] = { v1.x, v1.y, v1.z, v1.w };
			float b[] = { k, k, k, k };
			__m128 V1 = _mm_load_ps(a);
			__m128 V2 = _mm_load_ps(b);
			__m128 result = _mm_mul_ps(V1,V2);
			vec.x = result[0]; vec.y = result[1]; vec.z = result[2]; vec.w = result[3];
		#endif	
		return vec;
	}
	
	Vec3D glmVectorMul(Vec3D &v1,Vec3D &v2){
		Vec3D vec;
		#if NO_PARALLEL
			vec.x =  v1.x*v2.x;
			vec.y =  v1.y*v2.y;
			vec.z =  v1.z*v2.z;
		#endif
		
		#if PARALLEL_SIMD
			float a[] = { v1.x, v1.y, v1.z, v1.w };
			float b[] = { v2.x, v2.y, v2.z, v2.w };
			__m128 V1 = _mm_load_ps(a);
			__m128 V2 = _mm_load_ps(b);
			__m128 result = _mm_mul_ps(V1,V2);
			vec.x = result[0]; vec.y = result[1]; vec.z = result[2]; vec.w = result[3];
		#endif	
		return vec;
	}

	Vec3D glmVectorDiv(Vec3D &v1,float k){
		Vec3D vec;
		#if NO_PARALLEL
			vec.x =  v1.x/k;
			vec.y =  v1.y/k;
			vec.z =  v1.z/k;
		#endif

		#if PARALLEL_SIMD
			float a[] = { v1.x, v1.y, v1.z, v1.w };
			float b[] = { k, k, k, k };
			__m128 V1 = _mm_load_ps(a);
			__m128 V2 = _mm_load_ps(b);
			__m128 result = _mm_div_ps(V1,V2);
			vec.x = result[0]; vec.y = result[1]; vec.z = result[2]; vec.w = result[3];
		#endif	
		return vec;
	}
	
	Vec3D glmVectorDiv(Vec3D &v1,Vec3D &v2){
		Vec3D vec;
		#if NO_PARALLEL
			vec.x =  v1.x/v2.x;
			vec.y =  v1.y/v2.y;
			vec.z =  v1.z/v2.z;
		#endif

		#if PARALLEL_SIMD
			float a[] = { v1.x, v1.y, v1.z, v1.w };
			float b[] = { v2.x, v2.y, v2.z, v2.w };
			__m128 V1 = _mm_load_ps(a);
			__m128 V2 = _mm_load_ps(b);
			__m128 result = _mm_div_ps(V1,V2);
			vec.x = result[0]; vec.y = result[1]; vec.z = result[2]; vec.w = result[3];
		#endif	
		return vec;
	}

	float glmVectorDotProduct(Vec3D &v1,Vec3D &v2){
		#if NO_PARALLEL
			return v1.x*v2.x + v1.y*v2.y+v1.z*v2.z;
		#endif

		#if PARALLEL_SIMD
			float a[] = { v1.x, v1.y, v1.z, v1.w };
			float b[] = { v2.x, v2.y, v2.z, v2.w };
			__m128 V1 = _mm_load_ps(a);
			__m128 V2 = _mm_load_ps(b);
			__m128 result = _mm_mul_ps(V1,V2);
			return result[0]+result[1]+result[2];
		#endif	
	}

	float glmVectorLength(Vec3D &v){
		return sqrtf(glmVectorDotProduct(v,v));
	}

	Vec3D glmVectorNormalise(Vec3D &v1){
		Vec3D vec; 
		#if NO_PARALLEL
			float l = glmVectorLength(v1);
			vec.x =  v1.x/l;
			vec.y =  v1.y/l;
			vec.z =  v1.z/l;
		#endif

		#if PARALLEL_SIMD
			float l = glmVectorLength(v1);
			float a[] = { v1.x, v1.y, v1.z, v1.w };
			float b[] = { l, l, l, l };
			__m128 V1 = _mm_load_ps(a);
			__m128 V2 = _mm_load_ps(b);
			__m128 result = _mm_div_ps(V1,V2);
			vec.x = result[0]; vec.y = result[1]; vec.z = result[2]; vec.w = result[3];
		#endif	
		return vec;
	}

	Vec3D glmVectorCrossProduct(Vec3D &v1,Vec3D &v2){
		Vec3D vec;
		#if NO_PARALLEL
			vec.x = v1.y * v2.z - v1.z * v2.y;
			vec.y = v1.z * v2.x - v1.x * v2.z;
			vec.z = v1.x * v2.y - v1.y * v2.x;
		#endif
		#if PARALLEL_SIMD
			float a[] = { v1.y, v1.z, v1.x, 0.0f };
			float b[] = { v2.z, v2.x, v2.y, 0.0f };

			float c[] = { v1.z, v1.x, v1.y, 0.0f };
			float d[] = { v2.y, v2.z, v2.x, 0.0f };

			__m128 V1 = _mm_load_ps(a);
			__m128 V2 = _mm_load_ps(b);
			__m128 result1 = _mm_mul_ps(V1,V2);

			__m128 V3 = _mm_load_ps(c);
			__m128 V4 = _mm_load_ps(d);
			__m128 result2 = _mm_mul_ps(V3,V4);

			__m128 result = _mm_sub_ps(result1,result2);

			vec.x = result[0]; vec.y = result[1]; vec.z = result[2];
		#endif	
		return vec;
	}

	Vec3D glmMatrixMultiplyVector(Mat4x4 &m, Vec3D &i){
		Vec3D vec;
		#if NO_PARALLEL
			vec.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
			vec.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
			vec.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
			vec.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
		#endif
		
		#if PARALLEL_SIMD
			float x[] = { i.x,  i.x,  i.x,  i.x };
			float y[] = { i.y,  i.y,  i.y,  i.y };
			float z[] = { i.z,  i.z,  i.z,  i.z };
			float w[] = { i.w,  i.w,  i.w,  i.w };

			float m0[] = { m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3] };
			float m1[] = { m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3] };
			float m2[] = { m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3] };
			float m3[] = { m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3] };

			__m128 V1 = _mm_load_ps(x);
			__m128 V2 = _mm_load_ps(m0);
			__m128 result1 = _mm_mul_ps(V1,V2);

			__m128 V3 = _mm_load_ps(y);
			__m128 V4 = _mm_load_ps(m1);
			__m128 result2 = _mm_mul_ps(V3,V4);

			__m128 V5 = _mm_load_ps(z);
			__m128 V6 = _mm_load_ps(m2);
			__m128 result3 = _mm_mul_ps(V5,V6);

			__m128 V7 = _mm_load_ps(w);
			__m128 V8 = _mm_load_ps(m3);
			__m128 result4 = _mm_mul_ps(V7,V8);

			__m128 result5 = _mm_add_ps(result1,result2);
			__m128 result6 = _mm_add_ps(result3,result4);

			__m128 result = _mm_add_ps(result5,result6);
			vec.x = result[0]; vec.y = result[1]; vec.z = result[2]; vec.w = result[3];
		#endif
		return vec;
	}

	Mat4x4 glmMatrixMultiplyMatrix(Mat4x4 &m1, Mat4x4 &m2){
		Mat4x4 matrix;
		// #if NO_PARALLEL
			for(int c = 0; c < 4; c++){
				for(int r = 0; r < 4; r++){
					matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
				}
			}
		// #endif

		// #if PARALLEL_SIMD

		// #endif
		return matrix;
	}

	Mat4x4 glmMatrixQuickInverse(Mat4x4 &m){
		// #if NO_PARALLEL
			Mat4x4 matrix;
			matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
			matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
			matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
			matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
			matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
			matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
			matrix.m[3][3] = 1.0f;
			return matrix;
		// #endif
	}
};
