CXX := g++ -std=c++11
CXXFLAGS := -Wextra -Wall -g
OUT := main.out
INC_PATH := ./include/

$(OUT): Graph.o Node.o Edge.o
	$(CXX) $(CXXFLAGS) main.cpp -o $@

Graph.o: Graph.cpp ./include/Graph.hpp
	$(CXX) $(CXXFLAGS) Graph.cpp -c -o $@

Node.o: Node.cpp ./include/Node.hpp ./include/Edge.hpp
	$(CXX) $(CXXFLAGS) Node.cpp -c -o $@

Edge.o: Edge.cpp ./include/Edge.hpp
	$(CXX) $(CXXFLAGS) Edge.cpp -c -o $@

clean:
	rm -rf *.o *.out

