#include "./include/Graph.hpp"
#include "./include/Node.hpp"
#include "./include/Edge.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

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

int main()
{
    vector<string> topology = Graph::extract_topology();
    Graph graph(topology);
    cout << "Enter Your Command: "<<endl;
    command_handler(&graph);
    return 0;
}