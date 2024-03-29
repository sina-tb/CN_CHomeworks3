#include <iostream>
#include <sstream>
#include <chrono>

#include "./include/Graph.hpp"

const int INF = 1e9;

// Default Command and Notifiacation Strings
const string TOPOLGY = "topology";
const string TOPGY_MSG = "Enter your topology\n";
const string TOPGY_ERR = "Please provide a correct topology\n";
const string SAME_NODE = "Source and Destination nodes can not be the same\n";
const string NEG_EDGE = "Edges must be positive integers\n";

// Default Delimiters
const char IN_DEL = ' ';
const char TP_DEL = '-';


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

vector<string> getInput()
{
    vector<string> input;
    string inputStr;
    std::getline(std::cin, inputStr);
    input = splitByDelim(inputStr, IN_DEL);
    return input;
}

bool Graph::tp_format_checker(const vector<string> tp_form)
{
    if(tp_form.size() != 3)
    {
        cout << TOPGY_ERR;
        return false;
    }
    else if(tp_form[0] == tp_form[1])
    {
        cout << SAME_NODE;
        return false;
    }
    else if(std::stoi(tp_form[2]) <= 0)
    {
        cout << NEG_EDGE;
        return false;
    }
    else
    {
        return true;
    }
}

bool Graph::tp_valid(vector<string> &topology)
{
    if(topology.size() < 2 || topology[0] != TOPOLGY)
    {
        cout << TOPGY_ERR;
        return false;
    }
    // erasing the word topology
    topology.erase(topology.begin());
    for(string iinput : topology)
    {
        vector<string> tp_form = splitByDelim(iinput, TP_DEL);
        if(!tp_format_checker(tp_form))
        {
            return false;
        }
    }
    return true;
}

vector<string> Graph::extract_topology()
{
    vector<string> topology;
    do
    {
        cout << TOPGY_MSG;
        string topologyStr;
        std::getline(std::cin, topologyStr);
        topology = splitByDelim(topologyStr, IN_DEL);
    } while (!tp_valid(topology));
    return topology;
}

Graph::Graph(vector<string> topology) 
{
    for(string tp : topology)
    {
        vector<string> tp_holder = splitByDelim(tp, TP_DEL);
        int n1 = stoi(tp_holder[0]);
        int n2 = stoi(tp_holder[1]);
        int w = stoi(tp_holder[2]);

        Node* node1 = get_node(n1);
        Node* node2 = get_node(n2);

        if(node1 == nullptr)
        {
            add_node(n1)->addEdge(n1, n2, w);
        }
        else
        {
            node1->addEdge(n1, n2, w);
        }
        if(node2 == nullptr)
        {
            add_node(n2)->addEdge(n2, n1, w);
        }
        else
        {
            node2->addEdge(n2, n1, w);
        }
    }
}

Node* Graph::get_node(int id)
{
    for(auto inode = _nodes.begin();
        inode != _nodes.end();
        inode++)
    {
        if((*inode)->_id == id)
        {
            return (*inode);
        }
    }
    return nullptr;
}

Node* Graph::add_node(int id)
{
    Node* newNode = new Node(id);
    _nodes.push_back(newNode);
    return newNode;
}

void Graph::show()
{
    cout << "  | ";
    for(Node* inode : _nodes)
    {
        cout << inode->_id << " ";
    }
    cout << endl;
    cout << "---------------------------------------------- " <<endl;
    for(Node* inode : _nodes)
    {
        cout << inode->_id <<" | ";
        inode->printEdges(_nodes);
    }
}

void Graph::delete_edge(int node1, int node2)
{
    Node* index1 = get_node(node1);
    Node* index2 = get_node(node2);

    if(index1 != nullptr && index2 != nullptr)
    {
        for(auto iedge = index1->_edges.begin();
            iedge != index1->_edges.end();
            /*NOTHING*/)
        {
            if((*iedge)->_node2 == node2)
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
            if((*iedge)->_node2 == node1)
            {
                index2->_edges.erase(iedge);
                break;
            }
            ++iedge;
        }
        cout << "OK" << endl;
    }
    else{
        cout << "this edge doesn't exist" << endl;
    }
    
}

void Graph::modify_edge(int node1, int node2, int weight)
{
    Node* index1 = get_node(node1);
    Node* index2 = get_node(node2);

    bool edge1 = false, edge2 = false;

    if (index1 != nullptr && index2 != nullptr)
    {
        for(Edge* iedge : index1->_edges)
        {
            if(iedge->_node2 == node2)
            {
                iedge->_weight = weight;
                edge1 = true;
            }
        }

        for(Edge* iedge : index2->_edges)
        {
            if(iedge->_node2 == node1)
            {
                iedge->_weight = weight;
                edge2 = true;
            }
        }

        if (edge2 == false && edge1 == false)
        {
            index1->addEdge(node1, node2, weight);
            index2->addEdge(node2, node1, weight);
        }
        cout << "OK" << endl;
    }
    else
    {
        cout << "These Nodes Don't Exist" << endl;
    }
    
}

Graph::~Graph()
{
    // for(auto node_it = _nodes.begin();
    //     node_it != _nodes.end();
    //     node_it++)
    // {
    //     delete (*node_it);
    // }
}

int getDigitCount(int x)
{
    if (x == 0)
        return 1;
    int res = 0;
    while (x)
    {
        x /= 10;
        res++;
    }
    return res;
}


void Graph::link_state(int source)
{   
    auto start = std::chrono::steady_clock::now();
    int n = _nodes.size();
    vector<int> M;
    vector<int> C(n + 1,INF);
    vector<int> par(n + 1, -1);
    M.push_back(source);
    for(auto edge : get_node(source)->_edges)
    {
        if(edge->_node1 == source)
        {
            C[edge->_node2] = edge->_weight;
            par[edge->_node2] = source;
        }
        else
        { 
            C[edge->_node1] = edge->_weight;
            par[edge->_node1] = source;
        }
    }
    C[source] = 0;

    int iteration = 1;
    while (M.size() != n)
    {
        int min_cost = INF;
        int index = -1;
        for(int i = 1; i < n + 1 ; i++)
        {
            bool flag = false;
            for(int j = 0; j < M.size(); j++)
            {
                if(i == M[j]) 
                {
                    flag = true;
                }
            }
            if(flag)
            {
                continue;
            }
            if(C[i] < min_cost)
            {
                min_cost = C[i];
                index = i;
            }
        }
        cout << "   |Iter " + to_string(iteration) << ":" << endl;
        cout << "Dest|";
        for (auto node: _nodes)
        {
            int col = 4 - getDigitCount(node->_id);
            for (int i = 0; i < col; i++)
            {
                cout << " ";
            }
            cout << node->_id << "|";
        }
        cout << endl;
        cout << "Cost|";
        for (auto node: _nodes)
        {
            int ind = node->_id;
            int col = 4 - getDigitCount(C[ind]);
            if (C[ind] == INF)
                col = 2;
            for (int i = 0; i < col; i++)
            {
                cout << " ";
            }
            cout << (C[ind] == INF ? -1 : C[ind]) << "|";
        }
        cout << endl;
        for (int i = 0; i < (_nodes.size() + 1) * 5; i++)
            cout << "-";
        cout << endl;
        M.push_back(index);
        iteration++;

        for(int i = 1; i < n + 1 ; i++)
        {
            bool flag = false; 
            for(int j = 0; j < M.size(); j++)
            {
                if(i == M[j]) 
                {
                    flag = true;
                }
            }
            if(flag)
                continue;
            
            for(auto edge : get_node(index)->_edges)
            {   
                if(edge->_node1 == index)
                {
                    if(edge->_node2 != i)
                        continue;
                }
                else
                { 
                    if(edge->_node1 != i)
                        continue;
                }
                
                if(C[index] + edge->_weight < C[i])
                {
                    C[i] = C[index] + edge->_weight;
                    par[i] = index;
                }

            }
        }
    }
    
    string path;
    cout<<"\nPath: [s] -> [d]         Min-Cost         Shortest Path"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for (auto node: _nodes)
    {
        int ind = node->_id;
        path="";
        if (ind == source)
            continue;
        cout << "    [" << source << "] -> [" << ind << "]";
        int col = 15 - getDigitCount(ind);
        for (int i = 0; i < col; i++)
            cout << " ";
        cout<<C[ind];
        col= 15 - getDigitCount(C[ind]);
        for (int i = 0; i < col; i++)
                cout << " ";
        int p = ind;
        while (par[p] != -1)
        {   
            path=" -> "+to_string(p)+path;
            p = par[p];
        }
        cout << to_string(source) << path << endl;
    }
     
    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();
    cout << "Elapsed: " << elapsed_seconds << endl;
    return;
}

void Graph::distance_vector(int source)
{
    auto start = std::chrono::steady_clock::now(); 

    int n = _nodes.size();
    vector<int> dist(n + 1, INF);
    vector<int> par(n + 1, -1);

    dist[source] = 0;

    while (1)
    {
        bool updated = false;
        for (int i = 0; i < _nodes.size(); i++)
        {
            for (int j = 0; j < _nodes[i]->_edges.size(); j++)
            {
                int v = _nodes[i]->_edges[j]->_node1, u = _nodes[i]->_edges[j]->_node2, w = _nodes[i]->_edges[j]->_weight;
                if (dist[v] + w < dist[u])
                {
                    dist[u] = dist[v] + w;
                    par[u] = v;
                    updated = true;
                }
            }
        }
        if (!updated)
            break;
    }


    string path;
    int prev_p;
    cout<<"\nDest         NextHop         Dist         Shortest Path"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for (auto node: _nodes)
    {
        path="";
        if (node->_id == source)
            continue;
        cout <<  node->_id ;
        int col = 15 - getDigitCount(node->_id);
        for (int i = 0; i < col; i++)
            cout << " ";
        int p = node->_id;
        while (par[p] != -1)
        {   
            path=" -> "+to_string(p)+path;
            prev_p=p;
            p = par[p];
        }

        cout<<prev_p;
        col= 15 - getDigitCount(prev_p);
        for (int i = 0; i < col; i++)
                cout << " ";

        cout<<dist[node->_id];
        col= 12 - getDigitCount(dist[node->_id]);
        for (int i = 0; i < col; i++)
                cout << " ";

        cout << to_string(source) << path << endl;
    }

    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();
    cout << "Elapsed: " << elapsed_seconds << endl;
}
