all:
	g++ -std=c++11 -O3 main.cxx -o cube
cube: all
once: all
	-./cube > solutions
	-rm cube
