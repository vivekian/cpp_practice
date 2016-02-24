// Solution to assignment 2. 
// The class declarations are followed by the class definitions. 
//
// 

#include <algorithm> 
#include <cstdio> 
#include <functional> 
#include <iostream> 
#include <limits>
#include <map> 
#include <queue>
#include <random>
#include <stdint.h> 
#include <vector> 

using namespace std; 

// Maximum number of nodes in a graph
namespace { 
    const int MAXV = 100; 
}

// class - pair information about the end node and its associated cost 
class Node
{ 
    public: 
        Node(const uint32_t index, const uint32_t path_cost):
          idx(index), cost(path_cost) {}

        ~Node() {}

        uint32_t idx; 
        double cost; 
};  

// class - EdgeNode
// purpsose - data structure to hold edge data from one node to another node
//            including cost. also has a pointer to the next node in the edgelist
//            primarily intended for edgelist information
class EdgeNode 
{
    public: 
        EdgeNode(const uint32_t index, const uint32_t c):
            idx(index), cost(c), next(nullptr)
        {}

        uint32_t idx;       // index of the node in the graph
        double cost;    // weight of the edge - unsigned int since all positive weights
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
        void add(const uint32_t x, const uint32_t y, const uint32_t c, const bool IsReverse)
        { 
            EdgeNode* tmp = new EdgeNode(y, c);         // create a new empty node 
            tmp->next = nodelist[x];                    // insert at the beginning of list
            nodelist[x] = tmp;                          // append the rest of the list 
            degree[x]++;                                // increment the edge degree of node
        
            // create an edge from y to x as well
            if (!IsReverse) { 
                edges++;                                    // increment total edges
                add(y, x, c, true); 
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
          
           // iterate to find the edge from x to y and set the value(cost) correctly 
           while(p) { 
              if (p->idx == y) { 
                 p->cost = v; 
                 break; 
              }

              p = p->next; 
           }
        }

        uint32_t get_edge_value(const uint32_t x, const uint32_t y) 
        {
           EdgeNode* p = nodelist[x]; 
           uint32_t c = 0; 

           while(p) { 
              if (p->idx == y) { 
                c = p->cost; 
              }
              p = p->next; 
           } 

           return c; 
        }

        // return a list of neighbors associated with a vertex
        vector<Node> neighbours(const uint32_t x)
        { 
            vector<Node> n; 
            EdgeNode* p = nodelist[x]; 

            while(p) { 
                n.emplace_back(p->idx, p->cost); 
                p = p->next; 
            }

            return n; 
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
                    double path_cost = distance_dist(mt); 
               
                    // dont create a self loop or a duplicate edge
                    if (vertex != i && !g.adjacent(vertex, i)) { 
                        cout << "creating edge between " << i << " " << vertex << "with cost " << path_cost << endl; 
                        g.add(i, vertex, path_cost, false); 
                    }
               }
            }

        }

    private: 
        double density; 
        pair<double, double> dRange; 
};

class ShortestPath
{ 
    public: 
        ShortestPath(const Graph& g): graph(g) 
        {
            distance.resize(graph.V());
        };

        ~ShortestPath() {}

    void compute_shortest_paths()
    {
        // setup priority queue to sort items based on cost of the edges
        struct LessThan { 
            bool operator() (const Node& lhs, const Node& rhs) const { 
                return lhs.cost < rhs.cost; 
            }
        };
        function<bool(const Node& l, const Node& r)> lesserPath = [&] (const Node& a, const Node& b) 
                                                                    { return a.cost < b.cost; };
        priority_queue<Node, vector<Node>, LessThan> pq; 

        // take the first node and push it to priority queue with cost 0 
        // next take all the neighbors for this node and compute cost and store them in pq 
        // take the smallest cost node from pq and store it in visited vector 
        // now evaluate all its neighbors and store each one the pq
       
        pq.emplace(0, 0.0);
        distance[0] = 0; 

        for (int i=1; i<graph.V(); ++i) { 
            distance[i]= (MAX_DIST); 
        }
        
        while (!pq.empty()) { 
            Node curr = pq.top();
            pq.pop();
             
            vector<Node> nbrs = graph.neighbours(curr.idx); 
            
            for (auto & neighbor: nbrs) {
                double newcost= neighbor.cost + distance[curr.idx]; 
                if (newcost < distance[neighbor.idx]) { 
                    distance[neighbor.idx] = newcost; 
                    pq.emplace(neighbor.idx, newcost);
                }
            }
        }   
    }

    void print()
    { 
        for (int i=0; i<distance.size(); ++i) {
            cout << i << ": " << distance[i] << endl; 
        }
    }

    double avg_path_cost() 
    {
        double sum = accumulate(distance.begin(), distance.end(), 0.0); 
        return static_cast<double>(sum / distance.size());
    }

    private: 
        Graph graph;
        vector<double> distance; 
        const double MAX_DIST = 100.0; 
}; 

void run_example1()
{ 
    const int N = 6;  
    Graph g(N); 

    g.add(0, 1, 2, false); 
    g.add(0, 3, 4, false); 
    g.add(1, 2, 2, false); 
    g.add(2, 5, 2, false); 
    g.add(3, 4, 2, false); 
    g.add(3, 5, 1, false); 
    g.add(4, 5, 2, false); 
  
    g.print();

    ShortestPath sp(g); 
    sp.compute_shortest_paths(); 
    sp.print(); 

    cout << sp.avg_path_cost() << endl;  
}

void run_example2() 
{ 
    const int N = 10;
    Graph g(N); 
   
    GraphGenerator gen(0.1, make_pair(0, N-1)); 
    gen.generate(g);
    g.print(); 

    ShortestPath sp(g); 
    sp.compute_shortest_paths();
    sp.print(); 
    cout << sp.avg_path_cost() << endl;  
}   

int main() 
{
    run_example1(); 
    run_example2();
    return 0; 
}
