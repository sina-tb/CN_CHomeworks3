#include <string> 
#include <set>
#include <vector>


using namespace std;



class Edge
{
public:

    int node1;
    int node2;
    int weight;

    Edge(int n1, int n2, int w);
};


class Node
{

public:

    int id;
    vector <Edge> edges;

    Node(int d, vector <Edge> ed);
};



class Graph
{

public:

    vector <Node> nodes;

    Graph (string topology);
    void add_edge(Edge first, Edge second);
    void add_node(int n1, Edge ed);
    void show();
    void delete_edge(int node1, int node2);
    void modify_edge(int node1, int node2, int weight);
    int check_node(int id);
};

vector<string> splitByDelim(string text, char delimeter);