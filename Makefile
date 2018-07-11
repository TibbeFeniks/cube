cube:
	g++ -std=c++11 -O3 cube.cxx -o cube
once: cube
	-./cube
	-rm cube
