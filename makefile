# SETUP
CC=em++
OPTIONS=-O0 -s WASM=1 -std=c++1z -s FULL_ES3=1 -s USE_WEBGL2=1 -s USE_GLFW=3
DEBUGOPTIONS=$(OPTIONS) -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=2 -s SAFE_HEAP=1 -s DETERMINISTIC=1 --profiling-funcs -g -s DEMANGLE_SUPPORT=1 
# DIRECTORIES
DIR_ROOT=./src
DIR_SOURCE=$(DIR_ROOT)/onodrim-c
DIR_DIST=./bin

# FILES
FILE_MAIN = $(DIR_ROOT)/main.cpp
FILE_SOURCES = $(shell find $(DIR_SOURCE) -name *.cpp)
FILE_OUTPUT = -o $(DIR_DIST)/onodrim.html

build: .clear
	$(CC) $(OPTIONS) $(FILE_OUTPUT) $(FILE_MAIN) $(FILE_SOURCES)

debug: .clear
	$(CC) $(DEBUGOPTIONS) $(FILE_OUTPUT) $(FILE_MAIN) $(FILE_SOURCES)

.clear:
	rm -rf $(DISTDIR)/onodrim.js
	rm -rf $(DISTDIR)/onodrim.wasm
	rm -rf $(DISTDIR)/onodrim.html