#include "../include/gl.h"

namespace CenoGL{
	gl::gl(){}

	void gl::glColor3f(float r, float g, float b){
		Vec3D color; color.x = r;color.y = g;color.z = b;
		this->currentColor = color;
	}

	void gl::glVertex3f(float x, float y, float z){
		Vec3D vertex; vertex.x = x;vertex.y = y;vertex.z = z;
		this->vertexs.push_back(vertex);
	}
	
	void gl::glBegin(GLDrawMode mode){
		this->drawMode = mode;
	}
	
	void gl::glEnd(){
		switch (this->drawMode)
		{
		case GL_POINT:
			
			break;
		case GL_LINE:
			
			break;
		case GL_TRIANGLE:
			
			break;
		case GL_FILL_TRIANGLE:
		
			break;
		default:
			break;
		}
	}
	
	void gl::glFlush(){

	}

	gl::~gl(){}
};
			