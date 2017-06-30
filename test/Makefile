#OBJS specifies which files to compile as part of the project
OBJS = ../TerrainGenerator/*.cpp ../Vector2D.cpp ../Texture.cpp ../Log.h test.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I../include -I/usr/include/mingw -Dmain=SDL_main

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L../lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Wall -g -Wl,-subsystem,windows -std=c++0x -pthread

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lcygwin -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lnoise

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = test.exe

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)