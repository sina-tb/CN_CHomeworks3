#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <string> 
#include <set>
#include <vector>

#include "Node.hpp"
#include "Edge.hpp"

using namespace std;


class Graph
{

public:

    vector<Node> nodes;

    Graph(string topology);
    void add_edge(Edge first, Edge second);
    void add_node(int n1, Edge ed);
    void show();
    void delete_edge(int node1, int node2);
    void modify_edge(int node1, int node2, int weight);
    Node* get_node(int id);
};

vector<string> splitByDelim(string text, char delimeter);

#endif