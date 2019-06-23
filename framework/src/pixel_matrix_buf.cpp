#include "../include/pixel_matrix_buf.h"

using namespace CenoGL;


PixelMatrix::PixelMatrix(/* args */){

}

void PixelMatrix::setData(int numComponents,unsigned char *buffer){
	this->pixels = new Pixel*[this->height];
	for (int rows = 0; rows < this->height; rows++) {
		this->pixels[rows] = new Pixel[this->width];
    	for (int cols = 0; cols < this->width; cols ++) {
			Pixel *pixel = new Pixel();
			pixel->setColor(new Color(
				buffer[rows*this->width*numComponents + cols*numComponents + 0],
				buffer[rows*this->width*numComponents + cols*numComponents + 1],
				buffer[rows*this->width*numComponents + cols*numComponents + 2]));
			this->pixels[rows][cols] = *pixel;
    	}  
    }  
}

void  PixelMatrix::setPixel(int rows, int cols, Pixel *pixel){
	this->pixels[rows][cols] = *pixel;
}

void  PixelMatrix::setPixels(Pixel **pixels){
	this->pixels = pixels;
}
	

PixelMatrix::~PixelMatrix(){

}