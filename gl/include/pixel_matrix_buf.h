#ifndef __CENO_GL_PIXELMATRIX_H__
#define __CENO_GL_PIXELMATRIX_H__

#include "../include/pixel.h"

namespace CenoGL{
	class PixelMatrix
	{
	private:
		int height;
		int width;

		Pixel **pixels; // image data

	public:
		PixelMatrix(/* args */);

		void setWidth(int width){this->width = width;};
		void setHeight(int height){this->height = height;};

		void setData(int numComponents,unsigned char *buffer);

		void setPixel(int rows, int cols, Pixel *pixel);

		Pixel **getPixels(){return this->pixels;};
		void  setPixels(Pixel **pixels);

		int getWidth(){return this->width;}
		int getHeight(){return this->height;}



		~PixelMatrix();
	};
};

#endif // ! __CENO_GL_PIXELMATRIX_H__