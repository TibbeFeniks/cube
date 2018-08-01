SRC = cube.cxx piece.cxx cachedpiece.cxx common.cxx
cube: clean
	g++ -std=c++11 -O3 -Wall $(SRC) main.cxx -o cube
all: cube thread simple
once: cube
	-./cube > solutions
thread: clean
	g++ -std=c++11 -O3 -Wall -pthread $(SRC) tmain.cxx -o tcube
simple: clean
	g++ -std=c++11 -O3 -Wall -pthread $(SRC) smain.cxx -o scube
test: clean
	g++ -std=c++11 -O3 -Wall $(SRC) test.cxx -o test
clean:
	-rm *cube test
