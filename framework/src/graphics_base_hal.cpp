#include <stdint.h>
#include "../include/graphics_base_hal.h"
#include "../include/pixel_matrix_buf.h"

namespace CenoGL{
	GraphicsBaseHAL::GraphicsBaseHAL(){}
	void GraphicsBaseHAL::drawPixel(PixelMatrix *pixel_matrix_buf,int x,int y,uint32_t color){
		if(x < pixel_matrix_buf->getHeight() && x >=0 && y < pixel_matrix_buf->getWidth() && y>=0){
			pixel_matrix_buf->setPixel(x,y,new Pixel(new Color(
				(color & 0xFF000000) >> 24,
				(color & 0x00FF0000) >> 16,
				(color & 0x0000FF00) >> 8,
				(color & 0x000000FF) >> 0
			)));
		}
	}
	GraphicsBaseHAL::~GraphicsBaseHAL(){}


}; // CenoGL
