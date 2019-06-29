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
			GLDrawMode drawMode;
		public:
			gl();

			void glVertex3f(float x, float y, float z);
			void glColor3f(float r, float g, float b);

			// just tell the draw mode
			void glBegin(GLDrawMode mode);
			
			// draw to buffer 
			void glEnd();

			// i dont know what the the fuck does this func do? may be tell sdl to render?
			void glFlush();

			~gl();
	};
}; // CenoGL




#endif //! __CENO_GL_GRAPHICS_H__