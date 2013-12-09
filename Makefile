CC=g++
CFLAGS=-std=c++0x -Wall
CLIBS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -lGLEW

WC=cl
WCFLAGS=
WLIBS = $(wildcard lib/*.lib)
WLINKS = opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp)

all:
	@$(CC) -o dist/main $(CFLAGS) $(CLIBS) $(SOURCES) -I./lib -I./src -O1
	@cp -f res/* dist
	@dist/main

windows:
	@$(WC) /I.\lib /I.\src $(SOURCES) $(WLIBS) /link /out:dist\main.exe $(WLINKS)
	@rm '*.obj' -f
	@cp -f res/* dist
	@dist/main.exe
