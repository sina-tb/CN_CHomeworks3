#include "./include/Node.hpp"

#include <iostream>

Node::Node(int d, std::vector<Edge*> ed)
    : _id(d)
    , _edges(ed)
    {   }

Node::Node(int id)
    : _id(id)
    {   }

void Node::printEdges(const std::vector<Node*> nodes)
{
    for(Node* inode : nodes)
    {
        if(inode->_id == this->_id)
        {
            std:: cout << " 0" << " ";
            continue;
        }
        Edge* connectedEdge = getConEdge(inode);
        if(connectedEdge == nullptr)
        {
            std::cout << -1 << " ";
        }
        else
        {
            std::cout << connectedEdge->_weight << " ";
        }
    }
    std::cout << std::endl;
}

Edge* Node::getConEdge(const Node* checkNode)
{
    for(Edge* iedge : _edges)
    {
        if(iedge->_node2 == checkNode->_id)
        {
            return iedge;
        }
    }
    return nullptr;
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