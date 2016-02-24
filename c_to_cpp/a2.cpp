// Graph class representation

#include <algorithm> 
#include <cstdio> 
#include <iostream> 
#include <queue>
#include <random>
#include <stdint.h> 
#include <vector> 

using namespace std; 

// Maximum number of nodes in a graph
namespace { 
    const int MAXV = 100; 
}

// class - EdgeNode
// purpsose - data structure to hold edge data from one node to another node
//            including weight. also has a pointer to the next node in the edgelist
class EdgeNode 
{
    public: 
        EdgeNode(const uint32_t index, const uint32_t w):
            idx(index), weight(w), next(nullptr)
        {}

        uint32_t idx;       // index of the node in the graph
        uint32_t weight;    // weight of the edge - unsigned int since all positive weights
        EdgeNode* next;     // pointer to the next node in the list
};

// class - Graph 
//
// implementation of a edgelist form for the graph. 
// e.g. consider the graph below with 4 vertices
//      0 -> 1 -> 3 
//      1 -> 2 -> 0 
//      2 -> 1 
//      3 -> 1 
class Graph
{ 
    public: 
        // constructor to setup the graph. 
        // expects user to input the total number of vertices in the graph 
        Graph(const uint32_t num_vertices): 
            nvertices(num_vertices), edges(0)
        {
            nodelist.resize(MAXV);
            degree.resize(MAXV); 
            Initialize(); 
        }

        // destructor - empty as there is no dynamically allocated memory
        ~Graph(){}

        // setup the nodelist and the outward degree value for each node to 0. 
        void Initialize() 
        {
            fill(nodelist.begin(), nodelist.end(), nullptr); // initialize empty nodelist
            fill(degree.begin(), degree.end(), 0);           // initialize the degree to 0 for each node
        }

        int V() const { return nvertices; }       // return total number of vertices in the graph
        int E() const { return edges; }           // return total number of edges in the graph

        // method returns true if x and y are connected by an edge, else false. 
        bool adjacent(const uint32_t x, const uint32_t y) 
        { 
            bool ret = false;
            EdgeNode* p = nodelist[x]; 
            
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
        void add(const uint32_t x, const uint32_t y, bool IsReverse, const uint32_t w)
        { 
            EdgeNode* tmp = new EdgeNode(y, w);         // create a new empty node 
            tmp->next = nodelist[x];                    // insert at the beginning of list
            nodelist[x] = tmp;                          // append the rest of the list 
            degree[x]++;                                // increment the edge degree of node
        
            // create an edge from y to x as well
            if (!IsReverse) { 
                edges++;                                    // increment total edges
                add(y, x, true, w); 
            }
        } 
       
        // delete an edge from the graph  
        void del(const uint32_t x, const uint32_t y, bool IsReverse) 
        {
            // iterate with two pointers till we find the node 
            // once found, then have the previous node's next point to the 
            // next node.  
            EdgeNode* curr = nodelist[x]; 
            EdgeNode* prev = nodelist[x]; 
            
            while(curr) { 
                if (curr->idx == y) { 
                    prev->next = curr->next; 
                    delete curr; 
                    break; 
                }
                prev = curr; 
                curr=curr->next; 
            }

            // delete the reverse edge as well from y to x
            if (!IsReverse) { 
                del(y, x, true); 
            }
        }

        void set_edge_value(const uint32_t x, const uint32_t y, const uint32_t v) 
        {
           EdgeNode* p = nodelist[x]; 
          
           // iterate to find the edge from x to y and set the value(weight) correctly 
           while(p) { 
              if (p->idx == y) { 
                 p->weight = v; 
                 break; 
              }

              p = p->next; 
           }
        }

        uint32_t get_edge_value(const uint32_t x, const uint32_t y) 
        {
           EdgeNode* p = nodelist[x]; 
           uint32_t w = 0; 

           while(p) { 
              if (p->idx == y) { 
                w = p->weight; 
              }
              p = p->next; 
           } 

           return w; 
        }

        void print() 
        { 
           for (int i=0; i<nvertices; ++i) { 
                cout << i << " -> ";  
                EdgeNode* p = nodelist[i]; 

                while(p) {
                    cout << p->idx << " -> "; 
                    p = p->next; 
                }

                cout << endl; 
           }
        }               
     
    private:
        vector<EdgeNode*> nodelist; // adjacency list with edge information about each node  
        vector<uint32_t> degree;    // degree of each node in the graph 
        uint32_t nvertices;         // total number of vertices currently on the graph 
        uint32_t edges;             // total number of edges in the graph
};

class GraphGenerator 
{ 
    public: 
        GraphGenerator(const double edge_density, const pair<uint32_t, uint32_t> distance_range):
            density(edge_density), dRange(distance_range) 
        {}

        ~GraphGenerator() {}

        void generate(Graph& g) 
        {
            random_device rd;
            mt19937 mt(rd());
            uniform_int_distribution<uint32_t> vertex_dist(0, g.V()-1);
            uniform_real_distribution<double> distance_dist(dRange.first, dRange.second); 

            // compute the number of edges to generate per node based on the density
            uint32_t edges_per_node = g.V() * density;
            cout << edges_per_node << endl; 
            // generate edges for each node
            for (int i=0; i<g.V(); ++i) { 
              
               // create end point of an edge using 
                for (int e=0; e < edges_per_node; ++e) {
                    uint32_t vertex = vertex_dist(mt);
               
                    // dont create a self loop or a duplicate edge
                    if (vertex != i && !g.adjacent(vertex, i)) { 
                        cout << "creating edge between " << i << " " << vertex << endl; 
                        g.add(i, vertex, false, distance_dist(mt)); 
                    }
               }
            }

        }

    private: 
        double density; 
        pair<uint32_t, uint32_t> dRange; 
};

class Node
{ 
    public: 
    Node(const uint32_t index, const uint32_t path_cost):
      idx(index), cost(path_cost) {}

    ~Node() {}

    uint32_t idx; 
    uint32_t cost; 
};  

class ShortestPath
{ 
    public: 
        ShortestPath(const Graph& g): graph(g) 
        {
            // `visited.resize(g.V()); 
        };

        ~ShortestPath() {}

    void compute_shortest_paths()
    {
    }

    double avg_path_cost() 
    {
        double sum = accumulate(visited.begin(), visited.end(), 0.0,  [](double result, const Node& a) 
                                                                       { return a.cost + result; });
        return (sum / visited.size());
    }

    private: 
        Graph graph; 
        vector<Node> visited;
}; 

int main() 
{
    const int N = 10;  
    Graph g(N); 
    GraphGenerator gen(0.1, make_pair(0, N-1)); 
    gen.generate(g); 
    g.print(); 

    cout << g.E() << endl; 

    return 0; 
}
