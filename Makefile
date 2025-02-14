SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = play
INCLUDE_PATH = -Iinclude
LIB_PATH = -Llib \
           -L/opt/homebrew/Cellar/sdl2/2.30.11/lib \
           -L/opt/homebrew/Cellar/sdl_image/1.2.12_10/lib
CFLAGS = -Wall -g -O0 -std=c++11
LINKER_FLAGS = -lsdl2 

all:
	$(CC) $(CFLAGS) $(INCLUDE_PATH) $(LIB_PATH) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_FILES) $(LINKER_FLAGS)

run:
	$(BUILD_DIR)/$(OBJ_FILES)