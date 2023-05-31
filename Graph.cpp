#include "Graph.hpp"
#include <iostream>



vector<string> splitByDelim(string text, char delimeter)
{
    string cur = "";
    vector<string> words;
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == delimeter)
        {
            words.push_back(cur);
            cur = "";
        }
        else
        cur += text[i];
    }
    words.push_back(cur);
    return words;
}

Graph::Graph(string topology) 
{
    vector <string> words = splitByDelim(topology, ' ');
    for (int i = 0; i < words.size(); i++)
    {
        vector<string> edge = splitByDelim(words[i], '-');

        int n1 = stoi(edge[0]);
        int n2 = stoi(edge[1]);
        int w = stoi(edge[2]);

        Edge edge1(n1, n2, w);
        Edge edge2(n2, n1, w);

        int index1 = check_node(n1);
        int index2 = check_node(n2);
        
        if ( index1 == -1)
            add_node(n1, edge1);
        else
            nodes[index1].edges.push_back(edge1);
        if ( index2 == -1)
            add_node(n2, edge2);
        else
            nodes[index2].edges.push_back(edge2);
    }

}

int Graph::check_node(int id)
{
    for(int i = 0; i< nodes.size(); i++)
    {
        if ( nodes[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void Graph::add_node(int id , Edge edge)
{
    vector <Edge> ed;
    Node node(id, ed);
    node.edges.push_back(edge);
    nodes.push_back(node);
}

void Graph::show()
{
    cout << "  | ";
    for ( int i = 0; i < nodes.size(); i++)
        cout << nodes[i].id<<" ";
    cout << endl;
    cout << "---------------------------------------------- " <<endl;
    for ( int i = 0; i < nodes.size(); i++)
    {
        cout << nodes[i].id <<" | ";
        for ( int j = 0; j < nodes.size(); j++)
        {
                // print edges
        }
    }
}

void Graph::delete_edge(int node1, int node2)
{
    int index1 = check_node(node1);
    int index2 = check_node(node2);

    if ( index1 != -1 && index2 != -1)
    {
        for(int i = 0; i < nodes[index1].edges.size(); i++)
        {
            if( nodes[index1].edges[i].node2 == node2)
                nodes[index1].edges.erase(nodes[index1].edges.begin() + i);
        }
        for(int i = 0; i < nodes[index2].edges.size(); i++)
        {
            if( nodes[index2].edges[i].node1 == node1)
                nodes[index2].edges.erase(nodes[index2].edges.begin() + i);
        }
    }
    cout << "this edge doesn't exist";
}

void Graph::modify_edge(int node1, int node2, int weight)
{
    int index1 = check_node(node1);
    int index2 = check_node(node2);

    bool edge1 = false, edge2 = false;

    if ( index1 != -1 && index2 != -1)
    {
        for(int i = 0; i < nodes[index1].edges.size(); i++)
        {
            if( nodes[index1].edges[i].node2 == node2)
            {
                nodes[index1].edges[i].weight = weight;
                edge1 = true;
            }
        }
        if ( edge1 == false)
        {
            // add edge
        }
        for(int i = 0; i < nodes[index2].edges.size(); i++)
        {
            if( nodes[index2].edges[i].node2 == node2)
            {
                nodes[index2].edges[i].weight = weight;
                edge2 = true;
            }
        }
        if ( edge2 == false)
        {
            //add edge
        }
    }
    
}