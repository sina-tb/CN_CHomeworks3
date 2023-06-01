#include "./include/Node.hpp"

#include <iostream>

Node::Node(int d, std::vector<Edge*> ed)
    : _id(d)
    , _edges(ed)
    {   }

Node::Node(int id)
    : _id(id)
    {   }

void Node::printEdges()
{
    std::cout << _id << " ";
    for(Edge* iedge : _edges)
    {
        std::cout << iedge->_weight << " ";
    }
    std::cout << std::endl;
}

 Node Node::addEdge(int node1, int node2, int weight)
 {
    Edge* newEdge = new Edge(node1, node2, weight);
    _edges.push_back(newEdge);
    return *this;
 }

Node::~Node()
{
    // for(auto edge_it = _edges.begin();
    //     edge_it != _edges.end();
    //     edge_it++)
    // {
    //     delete (*edge_it);
    // } 
}