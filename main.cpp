#include "./include/Graph.hpp"
#include "./include/Node.hpp"
#include "./include/Edge.hpp"


int main()
{
    vector<string> topology = Graph::extract_topology();
    Graph graph(topology);
    graph.show();
    return 0;
}