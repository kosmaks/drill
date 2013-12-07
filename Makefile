CC=g++
CFLAGS=-std=c++0x -Wall
CLIBS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -lGLEW

SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp)
LIBS = $(wildcard lib/*.cpp) $(wildcard lib/**/*.cpp)

all:
	@$(CC) -o dist/main.exe $(CFLAGS) $(LIBS) $(SOURCES) -I./lib -I./src $(CLIBS) -O1
	@dist/main.exe
