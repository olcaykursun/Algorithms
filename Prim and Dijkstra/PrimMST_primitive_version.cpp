/*
Prim's Minimum Spanning Tree with implementation using std::priority_queue and some weird Olcay's stuff :)
Created on Thu Apr 22 14:46:49 2022
@author: Dr. Olcay Kursun, Spring 2022, AUM Dept. of Computer Science
*/

#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

enum class EdgeLabel { unlabeled_edge, tree_edge };
constexpr int unlabeled_vertex = 0;

struct Vertex;

struct Edge
{
    Edge(Vertex* v, double w) : otherEndPoint(v), weight(w) { }
    Vertex* otherEndPoint;
    EdgeLabel edgeLabel = EdgeLabel::unlabeled_edge;  //which may change to tree-edge
    Edge* oppositeDirection = nullptr;
    double weight;
};

struct Vertex
{
    Vertex* previousCopy = this;   //multiple copies are added to the priority queue but this link can be followed to find the original
    //priority_queue does not update the priority, so this is the solution I came up with: Just add light-weight (fake) vertices with updated priorities
    //those fake vertices point to the previousCopy and keep following that link until it points to itself, that's where the original vertex is.
    //findOriginalVertexInVector function is designed for that

    Vertex(string s) : name(s) { }
    string name;   //every node has a name like "a", "b", "c"... 
    int vertexLabel = unlabeled_vertex;   //0 is unvisited, then it will get a positive label
    vector<Edge*> edges;    //each vertex has a vector-array of edges
    double distToMST_forPriorityQueue = INT_MAX;   //original priority that is used in building the heap (so it's kept the same)
    double distToMST_forReal = INT_MAX;  //updated priority
    Edge* connectingEdge = nullptr;
};

class CloserToMST {   //returns true if lhs has lower priority than rhs
public:
    bool operator()(const Vertex* lhs, const Vertex* rhs) const 
    { 
        return lhs->distToMST_forPriorityQueue > rhs->distToMST_forPriorityQueue;
    };
};

void labelEdge(Edge* e, EdgeLabel l)
{
    if (e == nullptr)
        return;
    e->edgeLabel = l;                     //label the edge 
    if (e->oppositeDirection != nullptr)  //for undirected graphs 
        e->oppositeDirection->edgeLabel = l;  //also label the edge in the opposite/reverse direction
}

Vertex* findOriginalVertexInVector(Vertex* w)
{
    while (w->previousCopy != w)
        w = w->previousCopy;
    return w;
}

void updateReal(Vertex* w, double weight)
{
    while (w->previousCopy != w)
        w = w->previousCopy;
    w->distToMST_forReal = weight;
}

void PrimMSTAlgorithm(vector<Vertex*>& graph)
{
    int cnt = 0;
    Vertex* currNode = graph[0];
    currNode->distToMST_forPriorityQueue = 0;
    currNode->distToMST_forReal = 0;

    priority_queue<Vertex*, vector<Vertex*>, CloserToMST> q(graph.begin(), graph.end());

    while (!q.empty())
    {
        currNode = findOriginalVertexInVector(q.top());
        if (currNode->vertexLabel != unlabeled_vertex)
        {
            q.pop();
            continue;
        }
        currNode->vertexLabel = ++cnt;
        q.pop();
        labelEdge(currNode->connectingEdge, EdgeLabel::tree_edge);

        if (cnt == graph.size())   //once all vertices are in MST, stop updating already labeled vertices
            return;

        for (auto& e : currNode->edges)
        {
            Vertex* w = e->otherEndPoint;
            if (w->vertexLabel==unlabeled_vertex && e->weight < w->distToMST_forReal)
            {
                w->connectingEdge = e;
                Vertex* temp = new Vertex("temp_" + w->name);
                temp->previousCopy = w;
                temp->distToMST_forPriorityQueue = e->weight;
                updateReal(temp, e->weight);
                q.push(temp);
            }
        }
    }
}

vector<Vertex*> readGraph(string filename)
{
    int n;     // num_vertices
    string s;
    int v, w;  //graph v, w as in the book, edges will be from v to w
    double weight;

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
    while (infile >> v >> w >> weight)   //Read node index pairs and the weight
    {
        v--; w--;              //We start indices from 0
        Edge* edge_v_w = new Edge(graph[w], weight);   //v to w
        Edge* edge_w_v = new Edge(graph[v], weight);   //w to v because this is an undirected graph
        edge_v_w->oppositeDirection = edge_w_v;
        edge_w_v->oppositeDirection = edge_v_w;
        graph[v]->edges.push_back(edge_v_w);
        graph[w]->edges.push_back(edge_w_v);
    };
    return graph;
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

void printMST(const vector<Vertex*>& graph, string msg)
{
    double totalCost_version1 = 0;
    double totalCost_version2 = 0;
    cout << msg << "\n";
    for (const auto& v : graph)
    {
        cout << v->name << " is labeled " << v->vertexLabel << " " << v->distToMST_forReal << "\n";
        totalCost_version1 += v->distToMST_forReal;
        cout << "\tconnected via tree-edges to: ";
        for (const auto& e : v->edges)
        {
            if (e->edgeLabel == EdgeLabel::tree_edge)
            {
                Vertex* w = e->otherEndPoint;
                cout << w->name << " ";
                totalCost_version2 += e->weight;
            }
        }
        cout << "\n\n";
    }
    totalCost_version2 /= 2;  //each edge will be counted twice
    cout << "Total cost = " << totalCost_version1 << " = " << totalCost_version2 << "\n";
}

void printGraph(const vector<Vertex*>& graph, string msg)
{
    cout << msg << "\n";
    for (const auto& v : graph)
    {
        cout << v->name << "\n";
        cout << "\tconnected to: ";
        for (const auto& e : v->edges)
        {
            cout << e->otherEndPoint->name << " " << e->weight << "   ";
        }
        cout << "\n\n";
    }
}

int main()
{
    vector<Vertex*> graph;
    string filename;

    filename = "levitin_weighted.paj";    //the example on the DFS-BFS slides in Levitin's book, I added some random edge weights
//    filename = "karate_weighted.paj";  //Added random edge weights to the original at http://networkdata.ics.uci.edu/data/karate/karate.paj
    graph = readGraph(filename);
    printGraph(graph, "Input graph:");

    PrimMSTAlgorithm(graph);
    printMST(graph, "Prim's MST:");
    deleteGraph(graph);
}
