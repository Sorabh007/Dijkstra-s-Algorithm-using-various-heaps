#include "../include/Graph.h"
#include "../include/BinaryHeap.h"
#include "../include/BinomialHeap.h"

# define INF 0x3f3f3f3f

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<pair<int, int> > [V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    //adj[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int src, int heap_type)
{
    Heap *heap;

    switch(heap_type)
    {
        case BINARY: heap = new BinaryHeap(); break;
        case BINOMIAL: heap = new BinomialHeap(); break;
    }

    vector<int> dist(V, INF);

    (*heap).push(make_pair(0, src));

    dist[src] = 0;

    while ((*heap).top() != make_pair(-1, -1))
    {
        int u = (*heap).top().second;
        (*heap).pop();

        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                (*heap).push(make_pair(dist[v], v));
            }
        }
    }
    int sum=0;
    cout<<"Vertex Distance from Source"<<endl;
    for (int i = 0; i < V; ++i)
    {    
        cout<<i<<"\t\t"<<dist[i]<<endl;
        sum+=dist[i];
    }
    cout<<"Shortest distance: "<<sum<<endl;
    cout<<"Number of Operations performed : "<<(*heap).getOperations()<<endl;
    return;
}
