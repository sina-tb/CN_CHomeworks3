#include <iostream>
#include <sstream>

#include "./include/Graph.hpp"


vector<string> splitByDelim(string text, char delimiter)
{
    vector<string> words;
    stringstream ss;
    string temp;
    ss << text;
    while(std::getline(ss, temp, delimiter))
    {
        words.push_back(temp);
    }
    return words;
}

Graph::Graph(string topology) 
{
    vector<string> words = splitByDelim(topology, ' ');
    for (string iword : words)
    {
        vector<string> edge = splitByDelim(iword, '-');

        int n1 = stoi(edge[0]);
        int n2 = stoi(edge[1]);
        int w = stoi(edge[2]);

        Edge edge1(n1, n2, w);
        Edge edge2(n2, n1, w);

        Node* index1 = get_node(n1);
        Node* index2 = get_node(n2);
        
        if (index1 == nullptr)
            add_node(n1, edge1);
        else
            index1->_edges.push_back(edge1);
        if ( index2 == nullptr)
            add_node(n2, edge2);
        else
            index2->_edges.push_back(edge2);
    }

}

Node* Graph::get_node(int id)
{
    for(auto inode = nodes.begin();
        inode != nodes.end();
        inode++)
    {
        if((*inode)._id == id)
        {
            return &(*inode);
        }
    }
    return nullptr;
}

void Graph::add_node(int id , Edge edge)
{
    vector<Edge> ed;
    Node node(id, ed);
    node._edges.push_back(edge);
    nodes.push_back(node);
}

void Graph::show()
{
    cout << "  | ";
    for(Node inode : nodes)
    {
        cout << inode._id << " ";
    }
    cout << endl;
    cout << "---------------------------------------------- " <<endl;
    for(Node inode : nodes)
    {
        cout << inode._id <<" | ";
        for(Node jnode : nodes)
        {
            // print edges jnode.print();
        }
    }
}

void Graph::delete_edge(int node1, int node2)
{
    Node* index1 = get_node(node1);
    Node* index2 = get_node(node2);

    if(index1 != nullptr && index2 != nullptr)
    {
        for(auto iedge = index1->_edges.begin();
            iedge != index2->_edges.end();
             /*NOTHING*/)
        {
            if((*iedge)._node2 == node2)
            {
                index1->_edges.erase(iedge);
                break;
            }
            ++iedge;
        }

        for(auto iedge = index2->_edges.begin();
            iedge != index2->_edges.end();
            /*NOTHING*/)
        {
            if((*iedge)._node2 == node2)
            {
                index1->_edges.erase(iedge);
                break;
            }
            ++iedge;
        }
    }
    cout << "this edge doesn't exist" << endl;
}

void Graph::modify_edge(int node1, int node2, int weight)
{
    Node* index1 = get_node(node1);
    Node* index2 = get_node(node2);

    bool edge1 = false, edge2 = false;

    if (index1 != nullptr && index2 != nullptr)
    {
        for(Edge iedge : index1->_edges)
        {
            if(iedge._node2 == node2)
            {
                iedge._weight = weight;
                edge1 = true;
            }
        }

        for(Edge iedge : index2->_edges)
        {
            if(iedge._node1 == node1)
            {
                iedge._weight = weight;
                edge2 = true;
            }
        }

        if (edge2 == false && edge1 == false)
        {
            //add edge
        }
        else
        {
            // something is wrong
        }
    }
    
}