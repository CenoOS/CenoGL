# dir
BASE_DIR=/Users/neroyang/project/Ceno-GL

# include
INCLUDE_DIR=$(BASE_DIR)/framework/include/
INCLUDE_DIR+=$(BASE_DIR)/app/include/

# app
SRC=$(wildcard $(BASE_DIR)/app/src/*.cpp)
# framework
SRC+=$(wildcard $(BASE_DIR)/framework/src/*.cpp)

# build dir
BUILD_DIR=$(BASE_DIR)/app/build
# objs dir
OBJS_DIR=$(BASE_DIR)/app/obj
# asm dir
ASM_DIR=$(BASE_DIR)/app/asm

# compiler
CXX=g++

# build flags
CPP_FLAGS=-I$(INCLUDE_DIR) -std=c++11 -Wall
LINK_FLAGS=

# extera lib
LIB=-lstdc++ -ljpeg -lSDL2 -lSDL2main `sdl2-config --cflags --libs` -lpthread

run:	clean	all
	$(BUILD_DIR)/CenoGL
 
all:	CenoGL.o pixel.o pixel_matrix_buf.o   graphics_base_hal.o graphics2D.o graphics3D.o window.o
	$(CXX) -o $(BUILD_DIR)/CenoGL \
	$(OBJS_DIR)/CenoGL.o \
	$(OBJS_DIR)/pixel.o \
	$(OBJS_DIR)/pixel_matrix_buf.o \
	$(OBJS_DIR)/graphics2D.o \
	$(OBJS_DIR)/graphics3D.o \
	$(OBJS_DIR)/graphics_base_hal.o \
	$(OBJS_DIR)/window.o \
	$(LIB)

CenoGL.o:
	$(CXX) $(CPP_FLAGS) -o $(OBJS_DIR)/CenoGL.o -c $(BASE_DIR)/app/src/CenoGL.cpp $(LIB)

pixel.o:
	$(CXX) $(CPP_FLAGS) -o $(OBJS_DIR)/pixel.o -c $(BASE_DIR)/framework/src/pixel.cpp $(LIB)
pixel_matrix_buf.o:
	$(CXX) $(CPP_FLAGS) -o $(OBJS_DIR)/pixel_matrix_buf.o -c $(BASE_DIR)/framework/src/pixel_matrix_buf.cpp $(LIB)
graphics2D.o:
	$(CXX) $(CPP_FLAGS) -o $(OBJS_DIR)/graphics2D.o -c $(BASE_DIR)/framework/src/graphics2D.cpp $(LIB)
graphics3D.o:
	$(CXX) $(CPP_FLAGS) -o $(OBJS_DIR)/graphics3D.o -c $(BASE_DIR)/framework/src/graphics3D.cpp $(LIB)
graphics_base_hal.o:
	$(CXX) $(CPP_FLAGS) -o $(OBJS_DIR)/graphics_base_hal.o -c $(BASE_DIR)/framework/src/graphics_base_hal.cpp $(LIB)
window.o:
	$(CXX) $(CPP_FLAGS) -o $(OBJS_DIR)/window.o -c $(BASE_DIR)/framework/src/window.cpp $(LIB)


clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(BUILD_DIR)
	mkdir $(OBJS_DIR)
	mkdir $(BUILD_DIR)
