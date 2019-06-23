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
		float x,y,z;
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

			void multiplyMatrixVector(Vec3D &i, Vec3D &o, Mat4x4 &m);
			uint32_t getLumColor(uint32_t color,float lum);
			~Graphics3D();
	};
}; // CenoGL
#endif //! __CENO_GL_GRAPHICS_3D_H__

