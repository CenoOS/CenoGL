#ifndef __CENO_GL_GRAPHICS_H__
#define __CENO_GL_GRAPHICS_H__

#include <vector>
#include "../include/gl2D.h"
#include "../include/gl3D.h"

namespace CenoGL
{
	typedef enum GLDrawMode{
		GL_LINE,
		GL_POINT,
		GL_TRIANGLE,
		GL_FILL_TRIANGLE
	}GLDrawMode;


	class gl{
		private:
			std::vector<Vec3D> vertexs;
			Vec3D currentColor;
		public:
			gl();

			void glVertex3f();

			void glBegin(GLDrawMode mode);
			void glEnd();
			void glFlush();
			

			~gl();
	};
}; // CenoGL




#endif //! __CENO_GL_GRAPHICS_H__