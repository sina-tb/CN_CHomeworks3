#include <iostream>
#include <string>

#include "./include/Graph.hpp"
#include "./include/Node.hpp"
#include "./include/Edge.hpp"

// Commands
const string TOPLGY = "topology";
const string BGP = "bgp";
const string END = "end";

// Default Messages
const string END_MSG = 
"Thank you for using our Application\n\
Presented by:\n\
Sina Tabasi: 810199554\n\
Behrad Elmi: 810199557\n\
Kasra HajHeidari: 810199400\n";

const string DESGNT_TOP = "Error! Topology has already been define\n";
const string OK = "OK\n";
const string CMD_ERR = "Error! Enter your command correctly\n";

int main()
{
    Graph* graph = nullptr;
    vector<string> topology;
    while(1)
    {
        vector<string> input = getInput();
        if(input[0] == TOPLGY && input.size() > 1)
        {
            input.erase(input.begin());
            topology = Graph::extract_topology(input);
            if(topology.empty())
            {
                continue;
            }
            if(graph == nullptr)
            {
                graph = new Graph(topology);
                cout << OK;
            }
            else
            {
                cout << DESGNT_TOP;
                continue;
            }
        }
        else if(input[0] == BGP)
        {
            std::cout << 
                "bgp needs to be \
                implemented" << std::endl;
        }
        else if(input[0] == END)
        {
            std::cout << END_MSG;
            return 0;
        }
        else
        {
            cout << CMD_ERR;
            continue;
        }
    } 
    // graph.show();
    // graph.distance_vector(1);
    return 0;
}