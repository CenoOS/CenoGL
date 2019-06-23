#include "../include/window.h"
#include "../include/log.h"

using namespace CenoGL;

Window::Window() {

}

Window::Window(int windowWidth, int windowHeight, const char *windowName){
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
    this->windowName = (char *)windowName;
}

void Window::OnEvent(SDL_Event* Event) {

}

bool Window::Init() {
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
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	
	initPixelMatrixBuffer();	// init pixel buffer

    return true;
}

void Window::initPixelMatrixBuffer(){
	this->pixelMatrix = new PixelMatrix();
	this->pixelMatrix->setHeight(this->windowHeight);
	this->pixelMatrix->setWidth(this->windowWidth);

	Pixel** pixels = new Pixel*[this->windowHeight];
	for (int rows = 0; rows < this->windowHeight; rows++) {
		pixels[rows] = new Pixel[this->windowWidth];
    	for (int cols = 0; cols < this->windowWidth; cols ++) {
			Pixel *pixel = new Pixel();
			pixel->setColor(new Color(
				 0x00, 0x00, 0xFF, 0xFF
			));
			pixels[rows][cols] = *pixel;
    	}
    }
	this->pixelMatrix->setPixels(pixels);

	this->graphics2D = new Graphics2D(this->pixelMatrix);
}


void Window::Update() {
	this->graphics2D->drawLine(0,0,200,200,0xFF000000);
	this->graphics2D->drawCircle(100,100,20,0x00FF0000);
	this->graphics2D->drawTriangle(10,10,100,10,10,100,0xFFFFFF00);
	this->graphics2D->fillTriangle(120,120,210,120,120,210,0xFF00FF00);
}

void Window::Render() {
    SDL_RenderClear(renderer);
    for(int i = 0; i< this->pixelMatrix->getHeight(); i++){
        for(int j = 0; j< this->pixelMatrix->getWidth(); j++){
            SDL_SetRenderDrawColor(renderer, 
				pixelMatrix->getPixels()[i][j].getColor()->getR(),
			 	pixelMatrix->getPixels()[i][j].getColor()->getG(), 
			 	pixelMatrix->getPixels()[i][j].getColor()->getB(), 255);
            SDL_RenderDrawPoint(renderer, j, i);
        }
    }
    SDL_RenderPresent(renderer);
}

void Window::Cleanup() {
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


int Window::Execute() {
    if(!Init()) return 0;
        SDL_Event Event;
        while(running) {
            while(SDL_PollEvent(&Event) != 0) {
                OnEvent(&Event);
                if(Event.type == SDL_QUIT) running = false;
            }
            Update();
            Render();
            SDL_Delay(200); // Breath
        }
        Cleanup();
        return 1;
}


int Window::GetWindowWidth()  { return windowWidth;  }
int Window::GetWindowHeight() { return windowHeight;  }