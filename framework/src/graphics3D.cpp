#include <stdint.h>
#include <cmath>
#include "../include/graphics3D.h"

namespace CenoGL{

	Graphics3D::Graphics3D(PixelMatrix* pixels_buf){
		this->mGraphicsBaseHAL = new GraphicsBaseHAL();
		this->pixel_matrix_buffer = pixels_buf;
	}
	
	Graphics3D::~Graphics3D(){
	}



}; // CenoGL