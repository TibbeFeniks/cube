cube: clean
	g++ -std=c++11 -O3 -Wall cube.cxx piece.cxx cachedpiece.cxx main.cxx -o cube
all: cube
once: all
	-./cube > solutions
clean:
	-rm cube
