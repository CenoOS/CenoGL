#include <stdio.h>
#include <stdint.h>
#include "../../framework/include/window.h"

int main(){
    CenoGL::Window *window = new CenoGL::Window(480, 480, "CenoGL");
    window->Execute();
    return 0;
}