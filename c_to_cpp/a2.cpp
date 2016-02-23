// Graph class representation

#include <algorithm> 
#include <cstdio> 
#include <queue>
#include <stdint.h> 
#include <iostream> 

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
        EdgeNode(const uint32_t i, const uint32_t w):
            idx(i), weight(w), next(nullptr)
        {}

        uint32_t idx;       // index of the node in the graph
        uint32_t weight;    // weight of the edge 
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
            Initialize(); 
        }

        // destructor - empty as there is no dynamically allocated memory
        ~Graph(){}

        // setup the nodelist and the outward degree value for each node to 0. 
        void Initialize() 
        {
            fill(nodelist, nodelist+MAXV, nullptr); // initialize empty nodelist
            fill(degree, degree+MAXV, 0);           // initialize the degree to 0 for each node
        }

        int V() { return nvertices; }       // return total number of vertices in the graph
        int E() { return edges; }           // return total number of edges in the graph

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
        void add(const uint32_t x, const uint32_t y, bool IsReverse)
        { 
            EdgeNode* tmp = new EdgeNode(y, 0);         // create a new empty node 
            tmp->next = nodelist[x];                    // insert at the beginning of list
            nodelist[x] = tmp;                          // append the rest of the list 
            degree[x]++;                                // increment the edge degree of node
        
            // create an edge from y to x as well
            if (!IsReverse) { 
                edges++;                                    // increment total edges
                add(y, x, true); 
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
        EdgeNode* nodelist[MAXV];   // adjacency list with edge information about each node  
        uint32_t degree[MAXV];      // degree of each node in the graph 
        uint32_t nvertices;         // total number of vertices currently on the graph 
        uint32_t edges;             // total number of edges in the graph
};


int main() 
{ 
    Graph g(6); 

    g.add(0, 1, false);
    g.add(0, 5, false);
    g.add(1, 2, false);   
    g.add(1, 4, false);  
    g.add(2, 3, false);  
    g.add(3, 4, false);  
    g.add(4, 5, false);  
    g.print(); 

    cout << g.E() << endl; 

    return 0; 
}
