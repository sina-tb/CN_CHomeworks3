CXX := g++ -std=c++11
CXXFLAGS := -Wextra -Wall -g -Wno-sign-compare
OUT := main.out
INC_PATH := ./include/
OBJS := Graph.o Node.o Edge.o BGP.o Provider.o Customer.o

$(OUT): main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) main.cpp $(OBJS) -o $@

Graph.o: Graph.cpp ./include/Graph.hpp ./include/Node.hpp ./include/Edge.hpp
	$(CXX) $(CXXFLAGS) Graph.cpp -c -o $@

Node.o: Node.cpp ./include/Node.hpp ./include/Edge.hpp
	$(CXX) $(CXXFLAGS) Node.cpp -c -o $@

Edge.o: Edge.cpp ./include/Edge.hpp
	$(CXX) $(CXXFLAGS) Edge.cpp -c -o $@

BGP.o: BGP.cpp ./include/BGP.hpp ./include/Customer.hpp ./include/Provider.hpp
	$(CXX) $(CXXFLAGS) BGP.cpp -c -o $@

Provider.o: Provider.cpp ./include/Customer.hpp
	$(CXX) $(CXXFLAGS) Provider.cpp -c -o $@

Customer.o: Customer.cpp ./include/Provider.hpp
	$(CXX) $(CXXFLAGS) Customer.cpp -c -o $@

clean:
	rm -rf *.o *.out

