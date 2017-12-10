# SETUP
CC=em++
OPTIONS=-s WASM=1 -std=c++1z

# DIRECTORIES
DIR_ROOT=./Onodrim/Onodrim
DIR_SOURCE=$(DIR_ROOT)/src
DIR_DIST=./bin

# FILES
FILE_MAIN = $(DIR_ROOT)/Main.cpp
FILE_SOURCES = $(shell find $(DIR_SOURCE) -name *.cpp)
FILE_OUTPUT = $(DIR_DIST)/onodrim.html

build: .clear
	$(CC) $(OPTIONS) -o $(FILE_OUTPUT) $(FILE_MAIN) $(FILE_SOURCES)

.clear:
	rm -rf $(DISTDIR)/onodrim.js
	rm -rf $(DISTDIR)/onodrim.wasm
	rm -rf $(DISTDIR)/onodrim.html