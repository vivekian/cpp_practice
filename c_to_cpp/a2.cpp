//rudimentary graph representation and BFS solution. 

#include <algorithm> 
#include <cstdio> 
#include <queue>
#include <stdint.h> 

namespace { 
    const int MAXV = 100; 
}


// edgeNode holds the information about each edge for each edge
class edgeNode 
{
    public: 
        edgeNode(const uint32_t i, const uint32_t w):
            idx(i), weight(w), next(nullptr)
        {}

        uint32_t idx;       // index of the node in the graph
        uint32_t weight;    // weight of the edge 
        edgeNode* next;     // pointer to the next node in the list
};


class Graph
{ 
    public: 
        // constructor to setup the graph. 
        // expects user to input the total number of vertices in the graph 
        Graph(const uint32_t num_vertices): nvertices(num_vertices), edges(0)
        {
            Initialize(); 
        }

        // destructor - empty as there is no dynamically allocated memory
        ~Graph();

        // setup the nodelist and the outward degree value for each node to 0. 
        void Initialize() 
        {
            std::fill(nodelist, nodelist+MAXV, nullptr); // initialize empty lists
            std::fill(degree, degree+MAXV, 0);           // initialize the degree to 0 for each node
        }

        int V() { return nvertices; }       // return total number of vertices in the graph
        int E() { return edges; }           // return total number of edges in the graph

        // method returns true if x and y are connected by an edge, else false. 
        bool adjacent(const uint32_t x, const uint32_t y) 
        { 
            bool ret = false;
            edgeNode* p = nodelist[x]; 
            
            // iterate through all nodes to find a match
            while (p) { 
               if (p->idx == y) { 
                  ret = true; 
                  break; 
               }
               p = p->next;  
            }

            return ret; 
        } 
        
        // create an edge from node x to y
        // this requires to also create a node from y to x
        void add(const uint32_t x, const uint32_t y, bool IsReverse)
        { 
            edgeNode* tmp = new edgeNode(y, 0);         // create a new empty node 
            tmp->next = nodelist[x];                    // insert at the beginning of list
            nodelist[x] = tmp;                          // append the rest of the list 
            degree[x]++;                                // increment the edge degree of node
        
            // create an edge from y to x as well
            if (!IsReverse) { 
                edges++;                                    // increment total edges
                addEdge(y, x, true); 
            }
        } 

        void set_edge_value(const uint32_t x, const uint32_t y, const uint32_t v) 
        { 
        } 
            
    private:
        edgeNode* nodelist[MAXV];   // adjacency list with edge information about each node  
        uint32_t degree[MAXV];      // degree of each node in the graph 
        uint32_t nvertices;         // total number of vertices currently on the graph 
        uint32_t edges;             // total number of edges in the graph
};


typedef struct edgeNode { 
    uint32_t y; 
    edgeNode* next; 
} edgeNode;

typedef struct graph { 
    edgeNode* nodelist[MAXV]; 
    uint32_t degree[MAXV]; 
    uint32_t nvertices; 
} graph; 

void Initialize(graph* g) 
{ 
    std::fill(g->nodelist, g->nodelist + MAXV, nullptr); 
    std::fill(g->degree, g->degree + MAXV, 0); 
    g->nvertices = 0; 
}

// watch out for the recursive call to make sure there is an edge 
// from y to x as well. IsReverse just links on the other side.
void InsertEdge(graph* g, const int x, const int y, const bool IsReverse)
{
    edgeNode* node = new edgeNode; 
    node->y = y; 
    node->next = g->nodelist[x]; 
    g->nodelist[x] = node; 
    g->degree[x]++; 

    if (!IsReverse)
        InsertEdge(g, y, x, true);  
}

void PrintGraph(const graph* const g) 
{ 
    for (int i=0; i<g->nvertices; ++i) { 
        printf("%d -> ", i); 
        edgeNode* p = g->nodelist[i]; 
        while (p) { 
            printf("%d -> ", p->y);
            p = p->next;
        }
        printf("\n"); 
    }
}

void BFS(const graph* g, uint32_t d[])
{
    std::queue<int> q;
    
    for (int i=0; i<g->nvertices; ++i) 
        d[i] = UINT32_MAX; 

    q.push(0); 
    d[0] = 0; 

    while (!q.empty()) { 
        
        int node = q.front();
        q.pop();
        edgeNode* p = g->nodelist[node]; 
        
        while(p) {
          if (d[p->y] == UINT32_MAX) { 
                d[p->y] = d[node] + 1; 
                q.push(p->y); 
          } 
          p=p->next; 
        }

    }

    return; 
}

int main() 
{ 
    graph g; 
    Initialize(&g);
    g.nvertices = 6; 

    InsertEdge(&g, 0, 1, false);
    InsertEdge(&g, 0, 5, false);
    InsertEdge(&g, 1, 2, false);   
    InsertEdge(&g, 1, 4, false);  
    InsertEdge(&g, 2, 3, false);  
    InsertEdge(&g, 3, 4, false);  
    InsertEdge(&g, 4, 5, false);  
    
    PrintGraph(&g); 

    uint32_t d[MAXV]; 
    BFS(&g, d); 

    for(int i=0; i<g.nvertices; ++i) 
        printf("[%d]: %u\n", i, d[i]); 

    return 0; 
}
