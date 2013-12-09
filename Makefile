CC=g++
CFLAGS=-std=c++0x -Wall -DOPENGL
CLIBS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -lGLEW

DXLIB=C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86
WC=cl
WCFLAGS=/DDIRECTX /DOPENGL
WLIBS = $(wildcard lib/*.lib)
WLINKS = opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib '$(DXLIB)\d3d11.lib' '$(DXLIB)\d3dx11.lib' '$(DXLIB)\d3dx10.lib'

SOURCES = $(wildcard src/*.cpp) $(wildcard src/engine/core/*.cpp) $(wildcard src/engine/virtual/*.cpp) $(wildcard src/engine/world/*.cpp) $(wildcard src/engine/resources/*.cpp)
SOURCES_OGL = $(wildcard src/engine/opengl/*.cpp)
SOURCES_DX = $(wildcard src/engine/directx/*.cpp)

all:
	@$(CC) -o dist/main $(CFLAGS) $(CLIBS) $(SOURCES) $(SOURCES_OGL) -I./lib -I./src -O1
	@cp -f res/* dist
	@dist/main

windows:
	@$(WC) /I.\lib /I.\src '/IC:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include' $(WCFLAGS) $(SOURCES) $(SOURCES_OGL) $(SOURCES_DX) $(WLIBS) /link /out:dist\main.exe $(WLINKS)
	@rm '*.obj' -f
	@cp -f 'res/*' dist
	@dist/main.exe
