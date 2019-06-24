#ifndef __CENO_GL_GRAPHICS_3D_H__
#define __CENO_GL_GRAPHICS_3D_H__
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../include/graphics_base_hal.h"

namespace CenoGL
{


	struct Vec3D{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 1;
	};

	struct Triangle{
		Vec3D p[3];
		uint32_t color;
	};

	struct Mesh{
		std::vector<Triangle> tris;
		bool loadFromObjFiles(std::string fileName){
			std::ifstream f(fileName);
			if(!f.is_open()){
				return false;
			}
			std::vector<Vec3D> verts;
			while(!f.eof()){
				char line[128];
				f.getline(line,128);

				std::stringstream s;
				s << line;
				char junk;
				if(line[0]=='v'){
					Vec3D v;
					s >> junk >> v.x >> v.y >> v.z;
					verts.push_back(v);
				}
				if(line[0]=='f'){
					int f[3];
					s >> junk >> f[0] >> f[1] >> f[2];
					tris.push_back({verts[f[0]-1] , verts[f[1]-1] , verts[f[2]-1]});
				}
			}
		}
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

			uint32_t getLumColor(uint32_t color,float lum);
		
			Vec3D glVectorAdd(Vec3D &v1,Vec3D &v2); 
			Vec3D glVectorSub(Vec3D &v1,Vec3D &v2); 
			Vec3D glVectorMul(Vec3D &v1,float k); 
			Vec3D glVectorDiv(Vec3D &v1,float k); 
			float glVectorDotProduct(Vec3D &v1,Vec3D &v2); 
			float glVectorLength(Vec3D &v);
			Vec3D glVectorNormalise(Vec3D &v1); 
			Vec3D glVectorCrossProduct(Vec3D &v1,Vec3D &v2); 

			Vec3D glMatrixMultiplyVector(Mat4x4 &m, Vec3D &i);
			Mat4x4 glMatrixMultiplyMatrix(Mat4x4 &m1, Mat4x4 &m2);
			Mat4x4 glMatrixMakeIdentity();
			Mat4x4 glMatrixMakeRotationX(float angle);
			Mat4x4 glMatrixMakeRotationY(float angle);
			Mat4x4 glMatrixMakeRotationZ(float angle);
			Mat4x4 glMatrixMakeTranslation(float x, float y, float z);
			Mat4x4 glMatrixMakeProjection(float fovDegree, float aspectRatio, float near, float far);

			Mat4x4 glMatrixPointAt(Vec3D &pos,Vec3D &target,Vec3D &up);
			Mat4x4 glMatrixQuickInverse(Mat4x4 &m);

			Vec3D glVectorIntersectPlane(Vec3D &plane_p, Vec3D &plane_n, Vec3D &lineStart, Vec3D &lineEnd);
			int glTriangleClipAgainstPlane(Vec3D plane_p, Vec3D plane_n, Triangle &in_tri, Triangle &out_tri1, Triangle &out_tri2);

			

			~Graphics3D();
	};
}; // CenoGL
#endif //! __CENO_GL_GRAPHICS_3D_H__

