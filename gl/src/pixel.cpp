#include "../include/pixel.h"

using namespace CenoGL;


Color::Color(ui32 gray){
	this->color = 0;
	this->color |= gray << 24;
	this->color |= gray << 16;
	this->color |= gray << 8;
}


Color::Color(ui32 r, ui32 g, ui32 b){
	this->color = 0;
	this->color |= r << 24;
	this->color |= g << 16;
	this->color |= b << 8;
}

Color::Color(ui32 r, ui32 g, ui32 b, ui32 alpha){
	this->color = 0;
	this->color |= r << 24;
	this->color |= g << 16;
	this->color |= b << 8;
	this->color |= alpha;
}

ui32 Color::setR(ui32 r){
	this->color &= 0x00FFFFFF;
	this->color |= r << 24;
	return r;
}

ui32 Color::setG(ui32 g){
	this->color &= 0xFF00FFFF;
	this->color |= g << 16;
	return g;
}

ui32 Color::setB(ui32 b){
	this->color &= 0xFFFF00FF;
	this->color |= b << 8;
	return b;
}

ui32 Color::setAlpha(ui32 alpha){
	this->color &= 0xFFFFFF00;
	this->color |= alpha;
	return alpha;
}

ui32 Color::getR(){
	return this->color >> 24;
}

ui32 Color::getG(){
	return this->color >> 16 & 0xFF;
}

ui32 Color::getB(){
	return this->color >> 8 & 0xFF;
}

ui32 Color::getAlpha(){
	return this->color & 0xFF;
}


ui32  Color::getGray(/* TODO: Need multi mode */){
	return (this->getR() * 299 + this->getG() * 587 + this->getB() * 114 + 500)/1000;
}

ui32  Color::get2Val(){
	if((this->getR()+this->getR()+this->getR())/3 >= 0xFF >> 1 ){
		return 0xFF;
	}
	return 0;
}

Color::~Color(){}

Pixel::Pixel(){
	this->color = new Color(0, 0, 0);
}

Pixel::Pixel(Color *color){
	this->color = color;
}

Pixel::Pixel(ui32 r, ui32 g, ui32 b){
	Color *color = new Color(r, g, b);
	this->color = color;
}

Pixel::Pixel(ui32 r, ui32 g, ui32 b,ui32 alpha){
	Color *color = new Color(r, g, b, alpha);
	this->color = color;
}
	
Pixel::~Pixel(){
	delete color;
}