#ifndef __CENO_GL_PIXEL_H__
#define __CENO_GL_PIXEL_H__

namespace CenoGL{

	typedef unsigned int ui32;

	class Color{
		private:
			ui32 color;
		public:
			Color(ui32 gray);
			Color(ui32 r, ui32 g, ui32 b);
			Color(ui32 r, ui32 g, ui32 b, ui32 alpha);

			ui32 setR(ui32 r);
			ui32 setG(ui32 g);
			ui32 setB(ui32 b);
			ui32 setAlpha(ui32 alpha);

			ui32 getR();
			ui32 getG();
			ui32 getB();
			ui32 getAlpha();

			ui32 getGray(/* TODO: Need multi mode */);
			ui32 get2Val();

			ui32 defaultColorPalette[16] = {// 0xAABBGGRR
				0xFF000000, // BLACK
				0xFF800000, // DARK_BLUE
				0xFF008000, // DARK_GREEN
				0xFF808000, // DARK_CYAN
				0xFF000080, // DARK_RED
				0xFF800080, // DARK_MAGENTA
				0xFF008080, // DARK_YELLOW
				0xFFC0C0C0, // GREY
				0xFF808080, // DARK_GREY
				0xFFFF0000, // BLUE
				0xFF00FF00, // GREEN
				0xFFFFFF00, // CYAN
				0xFF0000FF, // RED
				0xFFFF00FF, // MAGENTA
				0xFF00FFFF, // YELLOW
				0xFFFFFFFF  // WHITE
			};

			~Color();
	};
	class Pixel
	{
	private:
		Color *color;

	public:

		Color *getColor(){return this->color;}
		void setColor(Color *color){this->color = color;}

		Pixel();
		Pixel(Color *color);
		Pixel(ui32 color);
		Pixel(ui32 r, ui32 g, ui32 b);
		Pixel(ui32 r, ui32 g, ui32 b,ui32 alpha);

	

		~Pixel();
	};
};

#endif // ! __CENO_GL_PIXEL_H__
