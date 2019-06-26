#include <stdio.h>
#include <stdint.h>
#include "../../gl/include/glut.h"

void display(){

}

void update(){
    SDL_Delay(100);
}

void keyboard(int key){

}

void mouseMove(int x,int y){

}

void mouseClick(int key){

}

int main(){
    CenoGL::glut gl;
    gl.glutCreateSDLWindow(640,480,"my glut window");
    gl.glutSetSDLWindowClearColor(0xFF0000FF);
    gl.glutSetDisplayFunc(&display);
    gl.glutSetIdleFunc(&update);
    gl.glutSetKeyPressedFunc(&keyboard);
    gl.glutSetMouseMoveFunc(&mouseMove);
    gl.glutSetMouseClickFunc(&mouseClick);
    gl.runGL();
}