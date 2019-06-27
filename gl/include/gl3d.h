#ifndef __CENO_GL_GRAPHICS_3D_H__
#define __CENO_GL_GRAPHICS_3D_H__
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../include/graphics_base_hal.h"
#include "../../glm/include/glm.h"

#define GL_CONSTANT_ATTENUATION    1.0f
#define GL_LINEAR_ATTENUATION 		0
#define GL_QUADRATIC_ATTENUATION   0

namespace CenoGL
{

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

	class gl3D{
		private:
			GraphicsBaseHAL *mGraphicsBaseHAL;
			PixelMatrix *pixel_matrix_buffer;
		public:
			gl3D(PixelMatrix* pixels_buf);	

			Vec3D glGetSpecularColor(Vec3D mspec,Vec3D sspec, Vec3D normal, Vec3D light,float shiness);
			Vec3D glGetSpecularColor(Vec3D mspec,Vec3D sspec,float lum);
			Vec3D glGetDiffuseColor(Vec3D mdiff,Vec3D sdiff, Vec3D normal, Vec3D light);
			Vec3D glGetAmbientColor(Vec3D mamb,Vec3D gamb);
			uint32_t glGetLumColor(uint32_t color,float lum);	
			float     glGetAttenuationFactor(float d);

			Vec3D glVertex3f(float x,float y,float z);

			uint32_t glColor3i(uint32_t r,uint32_t g,uint32_t b);
			Vec3D glColor3f(float r,float g,float b);
			Vec3D glColor1iTov(uint32_t color);
			uint32_t glColorvTo1i(Vec3D color);

		
			Mat4x4 glMatrixMakeIdentity();
			Mat4x4 glMatrixMakeRotationX(float angle);
			Mat4x4 glMatrixMakeRotationY(float angle);
			Mat4x4 glMatrixMakeRotationZ(float angle);
			Mat4x4 glMatrixMakeTranslation(float x, float y, float z);
			Mat4x4 glMatrixMakeProjection(float fovDegree, float aspectRatio, float near, float far);

			Mat4x4 glMatrixPointAt(Vec3D &pos,Vec3D &target,Vec3D &up);

			Vec3D glVectorIntersectPlane(Vec3D &plane_p, Vec3D &plane_n, Vec3D &lineStart, Vec3D &lineEnd);
			int   glTriangleClipAgainstPlane(Vec3D plane_p, Vec3D plane_n, Triangle &in_tri, Triangle &out_tri1, Triangle &out_tri2);

			

			~gl3D();
	};
}; // CenoGL
#endif //! __CENO_GL_GRAPHICS_3D_H__

