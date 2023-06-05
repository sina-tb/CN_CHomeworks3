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

    vector<Node*> _nodes;

    static vector<string> extract_topology();
    static bool tp_valid(vector<string> &topology);
    static bool tp_format_checker(const vector<string> tp_form);

    Graph(vector<string> topology);
    ~Graph();

    Node* add_node(int n1);
    void show();
    void delete_edge(int node1, int node2);
    void modify_edge(int node1, int node2, int weight);
    Node* get_node(int id);
    void distance_vector(int source);
    void link_state(int source);
};

vector<string> splitByDelim(string text, char delimeter);

#endif