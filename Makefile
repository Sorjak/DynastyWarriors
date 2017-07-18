#SRCS specifies which files to compile as part of the project
SRC_DIRS = ./src
BUILD_DIR = ./build

# SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
# SRCS := $(wildcard $(SRC_DIRS)/Systems/*.cpp $(SRC_DIRS)/Components/*.cpp $(SRC_DIRS)/Entities/*.cpp $(SRC_DIRS)/TerrainGenerator/*.cpp src/*.cpp )
SRCS := $(wildcard $(SRC_DIRS)/**/*.cpp $(SRC_DIRS)/*.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
# OBJS = $(SRCS:.cpp=.o)\

-include $(DEPS)

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I./include -I/usr/include/mingw -Dmain=SDL_main

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L./lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Wall -g -Wl,-subsystem,windows -std=c++0x -pthread -MMD -MP

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lcygwin -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lnoise

#EXE specifies the name of our exectuable
EXE = game.exe

# #This is the target that compiles our executable
# $(BUILD_DIR)/$(EXE): $(OBJS)
# 	$(CC) $< $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@

# PHONY: all
# all: ; $(info $$DEPS is [${DEPS}])

$(BUILD_DIR)/main.cpp.o: main.cpp
	$(CC) $< $(INCLUDE_PATHS)  $(COMPILER_FLAGS) -o $@ $(LINKER_FLAGS) $(LIBRARY_PATHS)

# $(BUILD_DIR)/$(EXE) : $(OBJS)
# 	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@



$(BUILD_DIR)/%.cpp.o: %.cpp
# 	$(MKDIR_P) $(dir $@)
# 	$(CC) $< $(INCLUDE_PATHS)  $(COMPILER_FLAGS) -o $@ $(LINKER_FLAGS) $(LIBRARY_PATHS)

MKDIR_P ?= mkdir -p

.PHONY: clean

clean :
	rm -rf $(BUILD_DIR)/*
