/*
Dijkstra's shortest path implementation using std::priority_queue adapted from my Prim's solution
Created on Thu Apr 24 22:59:58 2022
@author: Dr. Olcay Kursun, Spring 2022, AUM Dept. of Computer Science
*/

#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

constexpr int unlabeled_vertex = 0;

struct Vertex;

struct Edge
{
    Edge(Vertex* v, double w) : otherEndPoint(v), weight(w) { }
    Vertex* otherEndPoint;
    Edge* oppositeDirection = nullptr;
    double weight;
};

struct Vertex
{
    Vertex(string s) : name(s) { }
    string name;   //every node has a name like "a", "b", "c"... 
    int vertexLabel = unlabeled_vertex;   //0 is unvisited, then it will get a positive label
    vector<Edge*> edges;    //each vertex has a vector-array of edges
    double finalPriority = INT_MAX;  //updated priority
    Edge* connectingEdge = nullptr;
};

typedef std::pair<Vertex*, double> HeapObject;

class CompareHeapObjects {   //returns true if lhs has lower priority than rhs
public:
    bool operator()(const HeapObject& lhs, const HeapObject& rhs) const
    {
        return lhs.second > rhs.second;
    };
};

void DijkstraAlgorithm(vector<Vertex*>& graph)
{
    int cnt = 0;
    priority_queue<HeapObject, vector<HeapObject>, CompareHeapObjects> q;

    graph[0]->finalPriority = 0;
    for (auto& v : graph)
    {
        q.push(make_pair(v, v->finalPriority));
    }

    while (!q.empty())
    {
        pair<Vertex*, double> currNode = q.top();
        if (currNode.first->vertexLabel != unlabeled_vertex)
        {
            q.pop();
            continue;
        }
        currNode.first->vertexLabel = ++cnt;
        q.pop();

        if (cnt == graph.size())   //once all vertices are in MST, stop updating already labeled vertices
            return;

        for (auto& e : currNode.first->edges)
        {
            Vertex* w = e->otherEndPoint;
            double alternativeDist = currNode.first->finalPriority + e->weight;
            if (w->vertexLabel == unlabeled_vertex && alternativeDist < w->finalPriority)
            {
                w->connectingEdge = e;
                w->finalPriority = alternativeDist;
                q.push(make_pair(w, alternativeDist));
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

void printDijkstraPaths(const vector<Vertex*>& graph, string msg)
{
    cout << msg << "\n";
    for (const auto& v : graph)
    {
        cout << v->name << " has a path cost of " << v->finalPriority << "\n";
        vector<string> path;
        Vertex* w = v;
        while (w->connectingEdge != nullptr)
        {
            path.push_back(w->name);
            w = w->connectingEdge->oppositeDirection->otherEndPoint;
        }

        cout << "   The path is [" << graph[0]->name;
        for (auto w = path.rbegin(); w != path.rend(); ++w)
        {
            cout << ", " << *w;
        }
        cout << "]\n";
    }
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

    DijkstraAlgorithm(graph);
    printDijkstraPaths(graph, "Dijkstra paths:");
    deleteGraph(graph);
}
