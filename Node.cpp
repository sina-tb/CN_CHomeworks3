#include "./include/Node.hpp"

#include <iostream>

Node::Node(int d, std::vector<Edge> ed)
    : _id(d)
    , _edges(ed)
    {   }

void Node::print()
{
    std::cout << _id << " ";
    for(Edge iedge : _edges)
    {
        std::cout << iedge._weight << " ";
    }
    std::cout << std::endl;
}

 void Node::addEdge(Edge newEdge)
 {
    _edges.push_back(newEdge);
 }

 void Node::addEdge(int node1, int node2, int weight)
 {
    Edge newEdge(node1, node2, weight);
    _edges.push_back(newEdge);
 }
