#include "../include/window.h"
#include "../include/log.h"
#include <algorithm>


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
				 0x00, 0x00, 0x00, 0xFF
			));
			pixels[rows][cols] = *pixel;
    	}
    }
	this->pixelMatrix->setPixels(pixels);

	this->graphics2D = new Graphics2D(this->pixelMatrix);
	this->graphics3D = new Graphics3D(this->pixelMatrix);


	// mesh init
	// this->meshCube.tris = {
	// // SOUTH
	// 	{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
	// 	{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

	// 	// EAST                                                      
	// 	{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
	// 	{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

	// 	// NORTH                                                     
	// 	{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
	// 	{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

	// 	// WEST                                                      
	// 	{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
	// 	{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

	// 	// TOP                                                       
	// 	{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
	// 	{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

	// 	// BOTTOM                                                    
	// 	{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
	// 	{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
	// };

	this->meshCube.loadFromObjFiles("teapot.obj");

	// Projection Matrix
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = (float)this->windowHeight / (float)this->windowWidth;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	this->matProjection.m[0][0] = fAspectRatio * fFovRad;
	this->matProjection.m[1][1] = fFovRad;
	this->matProjection.m[2][2] = fFar / (fFar - fNear);
	this->matProjection.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	this->matProjection.m[2][3] = 1.0f;
	this->matProjection.m[3][3] = 0.0f;
}

float fTheta = 0.0f;
void Window::Update() {
	// this->graphics2D->drawLine(0,0,200,200,0xFF000000);
	// this->graphics2D->drawCircle(100,100,20,0x00FF0000);
	// this->graphics2D->drawTriangle(10,10,100,10,10,100,0xFFFFFF00);
	// this->graphics2D->fillTriangle(120,120,210,120,120,210,0xFF00FF00);
	// this->graphics2D->fillCircle(210,210,20,0xFFFF0000);

	Mat4x4 matRotZ, matRotX;
	fTheta +=0.1f;
	// Rotation Z
	matRotZ.m[0][0] = cosf(fTheta);
	matRotZ.m[0][1] = sinf(fTheta);
	matRotZ.m[1][0] = -sinf(fTheta);
	matRotZ.m[1][1] = cosf(fTheta);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;
	// Rotation X
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(fTheta * 0.5f);
	matRotX.m[1][2] = sinf(fTheta * 0.5f);
	matRotX.m[2][1] = -sinf(fTheta * 0.5f);
	matRotX.m[2][2] = cosf(fTheta * 0.5f);
	matRotX.m[3][3] = 1;

	std::vector<Triangle> vecTriangleToRaster;

	for(auto tri : this->meshCube.tris){
		Triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;
		tri.color = 0xFFD700FF;

		// Rotate in Z-Axis
		this->graphics3D->multiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
		this->graphics3D->multiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
		this->graphics3D->multiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

		// Rotate in X-Axis
		this->graphics3D->multiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
		this->graphics3D->multiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
		this->graphics3D->multiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

		// Offset into the screen
		triTranslated = triRotatedZX;
		triTranslated.p[0].z = triRotatedZX.p[0].z + 5.0f;
		triTranslated.p[1].z = triRotatedZX.p[1].z + 5.0f;
		triTranslated.p[2].z = triRotatedZX.p[2].z + 5.0f;

		Vec3D normal,line1,line2;
		line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
		line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
		line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

		line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
		line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
		line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

		normal.x = line1.y * line2.z - line1.z * line2.y;
		normal.y = line1.z * line2.x - line1.x * line2.z;
		normal.z = line1.x * line2.y - line1.y * line2.x;

		float l = sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
		normal.x/=l;	normal.y/=l;	normal.z/=l;

		if(normal.x * (triTranslated.p[0].x-this->vCamera.x) +
			normal.y * (triTranslated.p[0].y-this->vCamera.y) +
			normal.z * (triTranslated.p[0].z-this->vCamera.z) < 0.0f){
			
			//Illumination
			Vec3D lightDirection = {0.0f,0.0f,-1.0f};
			float l = sqrtf(lightDirection.x*lightDirection.x + lightDirection.y*lightDirection.y + lightDirection.z*lightDirection.z);
			lightDirection.x/=l;	lightDirection.y/=l;	lightDirection.z/=l;

			float dp = normal.x*lightDirection.x + normal.y*lightDirection.y + normal.z*lightDirection.z;
			uint32_t color = this->graphics3D->getLumColor(tri.color,dp);
			triTranslated.color = color;

			// Project triangles from 3D --> 2D
			this->graphics3D->multiplyMatrixVector(triTranslated.p[0], triProjected.p[0], this->matProjection);
			this->graphics3D->multiplyMatrixVector(triTranslated.p[1], triProjected.p[1],  this->matProjection);
			this->graphics3D->multiplyMatrixVector(triTranslated.p[2], triProjected.p[2],  this->matProjection);
			triProjected.color = triTranslated.color;

			// Scale into view
			triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
			triProjected.p[0].x *= 0.4f * (float)this->windowWidth;
			triProjected.p[0].y *= 0.4f * (float)this->windowHeight;
			triProjected.p[1].x *= 0.4f * (float)this->windowWidth;
			triProjected.p[1].y *= 0.4f * (float)this->windowHeight;
			triProjected.p[2].x *= 0.4f * (float)this->windowWidth;
			triProjected.p[2].y *= 0.4f * (float)this->windowHeight;

			vecTriangleToRaster.push_back(triProjected);
		}
	}

	// sort triangles from back to front
	sort(vecTriangleToRaster.begin(),vecTriangleToRaster.end(),[](Triangle &t1,Triangle &t2){
		float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
		float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
		return z1 > z2;
	});

	for(auto &tri : vecTriangleToRaster){
		this->graphics2D->fillTriangle(
			tri.p[0].x, tri.p[0].y,
			tri.p[1].x, tri.p[1].y,
			tri.p[2].x, tri.p[2].y,
			tri.color
		);
		// this->graphics2D->drawTriangle(
		// 	tri.p[0].x, tri.p[0].y,
		// 	tri.p[1].x, tri.p[1].y,
		// 	tri.p[2].x, tri.p[2].y,
		// 	0xFFFFFFFF
		// );
	}
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
		for(int i = 0; i< this->pixelMatrix->getHeight(); i++){
      			for(int j = 0; j< this->pixelMatrix->getWidth(); j++){
					  this->pixelMatrix->setPixel(i,j,new Pixel(new Color(0x00,0x00,0x00,0x00)));
      			}
 			}
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
            SDL_Delay(20); // Breath
        }
        Cleanup();
        return 1;
}


int Window::GetWindowWidth()  { return windowWidth;  }
int Window::GetWindowHeight() { return windowHeight;  }