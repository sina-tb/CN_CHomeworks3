#include "./include/Graph.hpp"
#include "./include/Node.hpp"
#include "./include/Edge.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "./include/Provider.hpp"
#include "./include/Provider.hpp"
#include "./include/BGP.hpp"

#define COMMAND_DELIM ' '

void command_handler(Graph* graph){

    string command,args;
    stringstream command_stream;
    vector<string> arg_list;

    while(getline(cin,command)){
        
        command_stream=stringstream(command);
        getline(command_stream,command,COMMAND_DELIM);
        getline(command_stream,args);
        if(command=="lsrp"){
            cout << args << endl;
            if (args.size()  == 0){
                for ( int i = 0; i < graph->_nodes.size(); i++)
                    graph->link_state(graph->_nodes[i]->_id);
            }
            else{
                arg_list=splitByDelim(args,'-');
                graph->link_state(stoi(args));
            }
        }
        else if(command=="dvrp"){
            cout << args << endl;
            if (args.size()  == 0){
                for ( int i = 0; i < graph->_nodes.size(); i++)
                    graph->distance_vector(graph->_nodes[i]->_id);
            }
            else{
                arg_list=splitByDelim(args,'-');
                graph->distance_vector(stoi(args));
            }
        }
        else if(command=="show"){
            graph->show();
        }
        else if(command=="modify"){
            arg_list=splitByDelim(args,'-');
            graph->modify_edge(stoi(arg_list[0]),stoi(arg_list[1]),stoi(arg_list[2]));
        }
        else if(command=="remove"){
            arg_list=splitByDelim(args,'-');
            graph->delete_edge(stoi(arg_list[0]),stoi(arg_list[1]));
        }
        else{
            cout<<"Error: Unknown Command"<<endl;
        }
        args = "";
        cout << "Enter Your Command: "<<endl;
    }
}

// Commands
const string TOPLGY = "topology";
const string BGP_CMD = "bgp";
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
const string ENTER_CMD = "Please Enter your command\n";
const string MAIN_MENU = "Choose one of the following options:\n\
1) Using topology command (and the two algorithms associated with it)\n\
2) Using bgp command (for bgp simulation)\n";

int main()
{
    while(1)
    {
        cout << MAIN_MENU;
        int main_inp;
        cin >> main_inp;
        if(main_inp == 1)
        {
            vector<string> topology = Graph::extract_topology();
            Graph graph(topology);
            cout << "Enter Your Command: "<<endl;
            command_handler(&graph);
        }
        else if(main_inp == 2)
        {
            cout << ENTER_CMD;
            BGP* bgp = nullptr;
            vector<string> input = getInput();
            if(input[0] == BGP_CMD && input.size() == 1)
            {
                bgp = new BGP();
                bgp->runBGP();
            }
            else if(input[0] == END && input.size() == 1)
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
    }
    return 0;
}