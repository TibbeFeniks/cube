cube: clean
	g++ -std=c++11 -O3 -Wall cube.cxx piece.cxx cachedpiece.cxx main.cxx -o cube
all: cube
once: all
	-./cube > solutions
thread: clean
	g++ -std=c++11 -O3 -Wall -pthread cube.cxx piece.cxx cachedpiece.cxx tmain.cxx -o tcube
test: clean
	g++ -std=c++11 -O3 -Wall cube.cxx piece.cxx cachedpiece.cxx test.cxx -o test
clean:
	-rm cube tcube test
