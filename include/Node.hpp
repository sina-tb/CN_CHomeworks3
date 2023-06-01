#ifndef _NODE_HPP_
#define _NODE_HPP_

#include <vector>

#include "Edge.hpp"

class Node
{

public:

    int _id;
    std::vector<Edge> _edges;
    
    Node(int d, std::vector<Edge> ed);

    void printEdges();
    void addEdge(Edge newEdge);
    void addEdge(int node1, int node2, int weight);
};

#endif