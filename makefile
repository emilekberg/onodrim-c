# SETUP
CC=em++
OPTIONS=-O0 -s WASM=1 -std=c++1z -s FULL_ES3=1 -s USE_WEBGL2=1 -s USE_GLFW=3 -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1 -s SAFE_HEAP=1 -s DETERMINISTIC=1

# DIRECTORIES
DIR_ROOT=./Onodrim/Onodrim
DIR_SOURCE=$(DIR_ROOT)/src
DIR_DIST=./bin

# FILES
FILE_MAIN = $(DIR_ROOT)/Main.cpp
FILE_SOURCES = $(shell find $(DIR_SOURCE) -name *.cpp)
FILE_OUTPUT = -o $(DIR_DIST)/onodrim.html

build: .clear
	$(CC) $(OPTIONS) $(FILE_OUTPUT) $(FILE_MAIN) $(FILE_SOURCES)

.clear:
	rm -rf $(DISTDIR)/onodrim.js
	rm -rf $(DISTDIR)/onodrim.wasm
	rm -rf $(DISTDIR)/onodrim.html