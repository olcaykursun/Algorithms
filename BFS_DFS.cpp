/*
BFS and DFS traversals with edge labels (tree edge, back edge, cross edge)
Created on Thu Apr 21 10:02:52 2022
@author: Dr. Olcay Kursun, Spring 2022, AUM Dept. of Computer Science
*/

#include <iostream>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

enum class EdgeLabel { unlabeled_edge, tree_edge, back_edge, cross_edge };
constexpr int unlabeled_vertex = 0;

struct Vertex;

struct Edge
{
    Edge(Vertex* v) : otherEndPoint(v) { }
    Vertex* otherEndPoint;
    EdgeLabel edgeLabel = EdgeLabel::unlabeled_edge;  //which will be changed to tree-edge or back/cross-edge
    Edge* oppositeDirection = nullptr;
};

struct Vertex
{
    Vertex(string s) : name(s) { }
    string name;   //every node has a name like "a", "b", "c"... 
    int vertexLabel = unlabeled_vertex;   //0 is unvisited, then it will get a positive label
    vector<Edge*> edges;    //each vertex has a vector-array of edges
};

void labelEdge(Edge* e, EdgeLabel l)
{
    e->edgeLabel = l;                     //label the edge 
    if (e->oppositeDirection != nullptr)  //for undirected graphs 
        e->oppositeDirection->edgeLabel = l;  //also label the edge in the opposite/reverse direction
}

void bfs(vector<Vertex*>& graph, Vertex* v, int& cnt)   //algorithm is adapted from Levitin's book
{
    queue<Vertex*> q;
    cnt++;
    v->vertexLabel = cnt;
    q.push(v);
    while (!q.empty())
    {
        Vertex* v = q.front();
        for (auto& e : v->edges)
        {
            if (e->edgeLabel != EdgeLabel::unlabeled_edge)
                continue; // skip the labeled edges (this can happen for undirected graphs)

            Vertex* w = e->otherEndPoint;
            if (w->vertexLabel == unlabeled_vertex)   //if neighbor is an unvisited vertex
            {
                cnt++;
                w->vertexLabel = cnt;  //label it as visited (with the order)
                q.push(w);
                labelEdge(e, EdgeLabel::tree_edge);    //label the edge as tree edge
            }
            else
                labelEdge(e, EdgeLabel::cross_edge);
        }
        q.pop();
    }
}

void BFS(vector<Vertex*>& graph)
{
    int cnt = 0;   //the counter to be used in node ordering

    //Do "bfs" for each connected component
    for (auto& v : graph)      //this loop will run only one iteration for connected graphs
        if (v->vertexLabel == unlabeled_vertex)
            bfs(graph, v, cnt);
}


void dfs(vector<Vertex*>& graph, Vertex* v, int& cnt)   //algorithm is adapted from Levitin's book
{
    cnt++;
    v->vertexLabel = cnt;
    for (auto& e : v->edges)
    {
        if (e->edgeLabel != EdgeLabel::unlabeled_edge)
            continue; // skip the labeled edges (this can happen for undirected graphs)

        auto& w = e->otherEndPoint;
        if (w->vertexLabel == unlabeled_vertex)          //if neighbor is an unvisited vertex
        {
            labelEdge(e, EdgeLabel::tree_edge);          //label the edge as tree edge
            dfs(graph, w, cnt);
        }
        else
            labelEdge(e, EdgeLabel::back_edge);
    }
}

void DFS(vector<Vertex*>& graph)
{
    int cnt = 0;   //the counter to be used in node ordering

    //Do "dfs" for each connected component
    for (auto& v : graph)      //this loop will run only one iteration for connected graphs
        if (v->vertexLabel == unlabeled_vertex)
            dfs(graph, v, cnt);
}


vector<Vertex*> readGraph(string filename)
{
    int n;     // num_vertices
    string s;
    int v, w;  //graph v, w as in the book, edges will be from v to w

    ifstream infile(filename);
    infile >> s >> n;              //Read the number of graph

    vector<Vertex*> graph;
    graph.reserve(n);

    for (int i = 0; i < n; i++)    //Read each node info line by line
    {
        infile >> v >> s;         //Node index and the name
        graph.push_back(new Vertex(s));
    }

    infile >> s;               //Skip the line in the file that contains string "*Edges"
    while (infile >> v >> w)   //Read node index pairs
    {
        v--; w--;              //We start indices from 0
        Edge* edge_v_w = new Edge(graph[w]);   //v to w
        Edge* edge_w_v = new Edge(graph[v]);   //w to v because this is an undirected graph
        edge_v_w->oppositeDirection = edge_w_v;
        edge_w_v->oppositeDirection = edge_v_w;
        graph[v]->edges.push_back(edge_v_w);
        graph[w]->edges.push_back(edge_w_v);
    };
    return graph;
}

void resetLabels(vector<Vertex*>& graph)
{
    for (auto& v : graph)
    {
        for (auto& e : v->edges)
        {
            labelEdge(e, EdgeLabel::unlabeled_edge);
        }
        v->vertexLabel = unlabeled_vertex;
    }
}

void deleteGraph(vector<Vertex*>& graph)
{
    for (auto& v : graph)
    {
        for (auto& e : v->edges)
        {
            delete e;     //remove the edge objects from the heap
        }
        v->edges.clear();  //remove the deallocated pointers from the vector
        delete v;
    }
    graph.clear();
}

void printOrdering(const vector<Vertex*>& graph, string msg)
{
    cout << msg << "\n";
    for (auto& v : graph)
    {
        cout << v->name << " is labeled " << v->vertexLabel << "\n";
        cout << "\tconnected via tree-edges to: ";
        for (auto& e : v->edges)
        {
            if (e->edgeLabel == EdgeLabel::tree_edge)
                cout << e->otherEndPoint->name << " ";
        }
        cout << "\n\n";
    }
}

int main()
{
    vector<Vertex*> graph;
    string filename;

    filename = "levitin.paj";    //the example on the DFS-BFS slides
//    filename = "karate.paj";  //Download from http://networkdata.ics.uci.edu/data/karate/karate.paj
    graph = readGraph(filename);

    BFS(graph);
    printOrdering(graph, "BFS:");

    resetLabels(graph);

    DFS(graph);
    printOrdering(graph, "DFS:");
    deleteGraph(graph);
}
