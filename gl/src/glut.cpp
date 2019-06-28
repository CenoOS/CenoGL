#include "../include/glut.h"
#include "../include/Log.h"


namespace CenoGL{

	glut::glut(){
		this->windowHeight = 480;
    	this->windowWidth = 640;
	}


	bool glut::init() {
   		if(SDL_Init(SDL_INIT_VIDEO) < 0) {
   		    Log("Unable to Init SDL: %s", SDL_GetError());
   		    return false;
   		}

   		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
   		    Log("Unable to Init hinting: %s", SDL_GetError());
   		}

   		if((window = SDL_CreateWindow(windowName,
   		                SDL_WINDOWPOS_UNDEFINED, 
   		                SDL_WINDOWPOS_UNDEFINED,
   		                windowWidth, windowHeight,
   		                SDL_WINDOW_SHOWN)) == NULL) {
   		    Log("Unable to create SDL Window: %s", SDL_GetError());
   		    return false;
   		}

   		primarySurface = SDL_GetWindowSurface(window);

   		if((renderer = SDL_GetRenderer(window)) == NULL) {
   		    Log("Unable to create renderer '%s'", SDL_GetError());
   		    return false;
   		}
   		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

		this->glutSetSDLWindowClearColor(0x000000FF);
		this->gl2d = new gl2D(this->pixel_matrix_buffer);

   		return true;
	}

	void glut::glutCreateSDLWindow(int width,int height,const char *name){
		this->windowHeight = height;
		this->windowWidth = width;
		this->windowName = name;
	}

	void glut::glutSetSDLWindowClearColor(uint32_t color){
		this->pixel_matrix_buffer = new PixelMatrix();
		this->pixel_matrix_buffer->setHeight(this->windowHeight);
		this->pixel_matrix_buffer->setWidth(this->windowWidth);

		this->backgroundColor = color;

		Pixel** pixels = new Pixel*[this->windowHeight];
		for (int rows = 0; rows < this->windowHeight; rows++) {
			pixels[rows] = new Pixel[this->windowWidth];
			for (int cols = 0; cols < this->windowWidth; cols ++) {
					Pixel *pixel = new Pixel();
					pixel->setColor(new Color(
						this->backgroundColor >> 24 && 0xFF,
						this->backgroundColor >> 16 && 0xFF,
						this->backgroundColor >> 8 && 0xFF,
						this->backgroundColor >> 0 && 0xFF
					));
					pixels[rows][cols] = *pixel;
			}
		}
		this->pixel_matrix_buffer->setPixels(pixels);
	}

	void glut::glutSetDisplayFunc(void (*display)()){
		this->show = display;
	}

	void glut::glutSetKeyPressedFunc(void (*keyPressed)(int key)){
		this->keyPressed = keyPressed;
	}

	void glut::glutSetMouseMoveFunc(void (*mouseMove)(int x,int y)){
		this->mouseMove = mouseMove;
	}

	void glut::glutSetMouseClickFunc(void (*mouseClick)(int key)){
		this->mouseClick = mouseClick;
	}

	void glut::glutSetIdleFunc(void (*update)()){
		this->idle = update;
	}
	

	void glut::update() {
		this->idle();
	}

	void glut::display() {

		this->gl2d->glDrawLine(0,0,200,200,0xFF000000);
		this->gl2d->glDrawCircle(100,100,20,0x00FF0000);
		this->gl2d->glDrawTriangle(10,10,100,10,10,100,0xFFFFFF00);
		this->gl2d->glFillTriangle(120,120,210,120,120,210,0xFF00FF00);
		this->gl2d->glFillCircle(210,210,20,0xFFFF0000);

		this->show();
		SDL_RenderClear(renderer);
		for(int i = 0; i< this->pixel_matrix_buffer->getHeight(); i++){
			for(int j = 0; j< this->pixel_matrix_buffer->getWidth(); j++){
				SDL_SetRenderDrawColor(renderer, 
					pixel_matrix_buffer->getPixels()[i][j].getColor()->getR(),
					pixel_matrix_buffer->getPixels()[i][j].getColor()->getG(), 
					pixel_matrix_buffer->getPixels()[i][j].getColor()->getB(), 255);
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
		SDL_RenderPresent(renderer);

		
		this->clear();
	}

	void glut::clear(){
		for(int i = 0; i< this->pixel_matrix_buffer->getHeight(); i++){
	    	for(int j = 0; j< this->pixel_matrix_buffer->getWidth(); j++){
				this->pixel_matrix_buffer->setPixel(i,j,new Pixel(
					new Color(
						this->backgroundColor>>24 & 0xFF,
						this->backgroundColor>>16 & 0xFF,
						this->backgroundColor>>8 & 0xFF,
						0xFF)));
	    	}
	 	}
	}

	void glut::cleanUp() {
		if(renderer) {
			SDL_DestroyRenderer(renderer);
			renderer = NULL;
		}

		if(window) {
		SDL_DestroyWindow(window);
			window = NULL;
		}
		SDL_Quit();
	}

	template<size_t size>
	void glut::onKeyPressed(bool(&keys)[size]){
		// this->keyPressed()
	}

	void glut::runGL() {
		if(!init()){ 
			exit(0);
		}else{
			SDL_Event Event;
			bool keysHeld[323] = {false};
			while(running) {
				while(SDL_PollEvent(&Event) != 0) {
					onEvent(&Event);
					if(Event.type == SDL_QUIT) {
						running = false;
					}
					if (Event.type == SDL_KEYDOWN){
						keysHeld[0xFF & Event.key.keysym.sym] = true;	
					}	
					if (Event.type == SDL_KEYUP){
						keysHeld[0xFF & Event.key.keysym.sym] = false;
					}
				}
				this->onKeyPressed(keysHeld);
				update();
				display();
				// SDL_Delay(20); // Breath
			}
			cleanUp();
			exit(0);
		}
	}

	void glut::onEvent(SDL_Event* Event) {

	}
	
	glut::~glut(){}
} // namespace CenoGL



