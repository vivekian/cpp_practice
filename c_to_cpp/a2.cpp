// Solution to assignment 2. 
// The class declarations are followed by the class definitions. 
//
// To compile this program on Linux: 
//      $CC -std=c++14 a2.cpp 
//      where CC = g++ or clang++
//
// I have not compiled it on windows, but don't see why there would be any issues. Just make 
// sure that C++14 support is turned on. 
//
// There are primarily 3 classes: Graph, GraphGenerator and ShortestPath.
// ShortestPath uses a STL priority queue which sorts objects based on distance cost.
//
// There are 3 examples run from main(), one is a hand-crafted graph to make sure there is sanity. 
// The other two examples involve simulating the graphs based on input - edge density, number of vertices and distance range.   

#include <algorithm> 
#include <cstdio> 
#include <functional> 
#include <iostream> 
#include <queue>
#include <random>
#include <stdint.h> 
#include <vector> 

using namespace std; 

// Maximum number of nodes in a graph
// anonymous namespace is the C++ way to declare static variable in a class.
namespace { 
    const int MAXV = 100; 
}

// Node has the most fundamental information about itself (index) and (cost). 
// Its implicitly associated with a source node to which its connected.
class Node
{ 
    public: 
        Node(const uint32_t index, const uint32_t path_cost):
          idx(index), cost(path_cost) {}

        ~Node() {}

        uint32_t idx; 
        double cost; 
};  

// data structure to hold edge data from one node to another node
// including cost. also has a pointer to the next node in the edgelist
// primarily intended for edgelist information for the graph.
class EdgeNode 
{
    public: 
        EdgeNode(const uint32_t index, const uint32_t c):
            idx(index), cost(c), next(nullptr)
        {}

        uint32_t idx;       // index of the node in the graph
        double cost;        // cost distance of the edge - unsigned int since all positive weights
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
            nvertices(num_vertices), num_edges(0)
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

        // return total number of vertices in the graph
        int V() const { return nvertices; }      

        // return total number of num_edges in the graph
        int E() const { return num_edges; }          
    
        // print the contents of the graph 
        void print() const;
    
        // create an edge from node x to y
        void add(const uint32_t x, const uint32_t y, const uint32_t c, const bool IsReverse);

        // delete an edge from the graph  
        void del(const uint32_t x, const uint32_t y, bool IsReverse);

        // set the value of an edge
        void set_edge_value(const uint32_t x, const uint32_t y, const uint32_t v);

        // get the cost of an edge 
        uint32_t get_edge_value(const uint32_t x, const uint32_t y) const;

        // return a list of neighbors associated with a vertex
        vector<Node> neighbours(const uint32_t x) const; 
           
        // method returns true if x and y are connected by an edge, else false. 
        bool adjacent(const uint32_t x, const uint32_t y);
    
    private:
        // adjacency list for each node in a linked list. 
        vector<EdgeNode*> nodelist; 

        // degree of each node in the graph  
        vector<uint32_t> degree;  
        
        // total number of vertices currently on graph 
        uint32_t nvertices;             
        
        // total number of edges on the graph
        uint32_t num_edges;               
};


// method returns true if x and y are connected by an edge, else false. 
bool Graph::adjacent(const uint32_t x, const uint32_t y) 
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
// this requires to also create a node from y to x since the graph is undirected
void Graph::add(const uint32_t x, const uint32_t y, const uint32_t c, const bool IsReverse)
{ 
    EdgeNode* tmp = new EdgeNode(y, c);         // create a new empty node 
    tmp->next = nodelist[x];                    // insert at the beginning of list
    nodelist[x] = tmp;                          // append the rest of the list 
    degree[x]++;                                // increment the edge degree of node

    // create an edge from y to x as well
    if (!IsReverse) { 
        num_edges++;                                    // increment total edges
        add(y, x, c, true); 
    }
} 

// delete an edge from the graph  
void Graph::del(const uint32_t x, const uint32_t y, bool IsReverse) 
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

// set the cost of an edge based on its two coordinates
void Graph::set_edge_value(const uint32_t x, const uint32_t y, const uint32_t v) 
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

// get the cost of an edge 
uint32_t Graph::get_edge_value(const uint32_t x, const uint32_t y) const
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
vector<Node> Graph::neighbours(const uint32_t x) const
{ 
    vector<Node> n; 
    EdgeNode* p = nodelist[x]; 

    while(p) { 
        n.emplace_back(p->idx, p->cost); 
        p = p->next; 
    }

    return n; 
}

// print the contents of a graph
void Graph::print() const
{
   cout << "graph contents\n"; 

   for (int i=0; i<nvertices; ++i) { 
        cout << i << ": ";  
        EdgeNode* p = nodelist[i]; 

        while(p) {
            cout << p->idx ; 
            p = p->next;
            
            if (p)  
                cout << ",";
        }

        cout << endl; 
   }
}               
 

// class to generate a simulated graph based on edge density and distance range. 
class GraphGenerator 
{ 
    public: 
        GraphGenerator(const double edge_density, const pair<uint32_t, uint32_t> distance_range):
            density(edge_density), dRange(distance_range) 
        {}

        ~GraphGenerator() {}

        // generate a graph based on edge density and distance range 
        void generate(Graph& g); 

    private: 
        // edge density for a graph between 0 to 1
        double density; 

        // distance range across which random distances are picked up.
        pair<double, double> dRange; 
};

void GraphGenerator::generate(Graph& g) 
{ 
    // Although the assignment asks to generate a monte carlo simulation, sticking here with a simple 
    // uniform distribution. 
    // There are two distributions: 
    //      vertex_dist is to generate vertices for a specific edge based on density 
    //      distance_dist is to generate cost distance for each edge
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<uint32_t> vertex_dist(0, g.V()-1);
    uniform_real_distribution<double> distance_dist(dRange.first, dRange.second); 

    // compute the number of edges to generate per node based on the density
    uint32_t edges_per_node = g.V() * density;

    // generate edges for each node
    for (int i=0; i<g.V(); ++i) { 
      
       // create end point of an edge
        for (int e=0; e < edges_per_node; ++e) {
            uint32_t vertex = vertex_dist(mt);
            double path_cost = distance_dist(mt); 
       
            // dont create a self loop or a duplicate edge
            if (vertex != i && !g.adjacent(vertex, i)) { 
                g.add(i, vertex, path_cost, false); 
            }
       }
    }
}

// implements Djikastra's shortest path algorithm 
class ShortestPath
{ 
    public: 
        // constructor takes Graph object reference 
        ShortestPath(const Graph& g): graph(g) 
        {
            // resize distance array to be of size V vertices
            distance.resize(graph.V());
        };

        ~ShortestPath() {}

        // computer shortest paths for each vertex from the source
        void compute_shortest_paths(); 

        // print the shortest distance for each vertex from the source 
        void print() const; 

        // compute the average cost path for all nodes from source 
        double avg_path_cost() const;  

    private: 
        // store the reference to graph object on which to operate
        Graph graph;

        // distance vector for shortest distance from source to each node
        vector<double> distance; 
        const double MAX_DIST = 100.0; 
}; 

void ShortestPath::compute_shortest_paths()
{
    // setup priority queue to sort items based on cost of the edges
    struct LessThan { 
        bool operator() (const Node& lhs, const Node& rhs) const { 
            return lhs.cost < rhs.cost; 
        }
    };

    priority_queue<Node, vector<Node>, LessThan> pq; 

    // we assume the source is 0 and distance of node 0 to itself is 0.
    pq.emplace(0, 0.0);
    distance[0] = 0; 

    // for all the other nodes, setup a max distance 
    for (int i=1; i<graph.V(); ++i) { 
        distance[i]= (MAX_DIST); 
    }
    
    while (!pq.empty()) { 
        // priority queue is based on minheap, so the min cost vertex is always picked
        Node curr = pq.top();
        pq.pop();
         
        vector<Node> nbrs = graph.neighbours(curr.idx); 
    
        // for each neighbor compute the new cost from source to node
        // if the new cost is lower than existing cost, then update distance array
        // and add the data point to the priority queue 
        for (auto & neighbor: nbrs) {
            double newcost= neighbor.cost + distance[curr.idx]; 
            if (newcost < distance[neighbor.idx]) { 
                distance[neighbor.idx] = newcost; 
                pq.emplace(neighbor.idx, newcost);
            }
        }
    }   
}

void ShortestPath::print() const 
{ 
    for (int i=0; i<distance.size(); ++i) {
        cout << i << ": " << distance[i] << endl; 
    }
}

double ShortestPath::avg_path_cost() const
{ 
    double sum = accumulate(distance.begin(), distance.end(), 0.0); 
    return static_cast<double>(sum / distance.size());
}

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

void run_example3() 
{ 
    const int N = 50;
    Graph g(N); 
   
    GraphGenerator gen(0.4, make_pair(0, N-1)); 
    gen.generate(g);

    ShortestPath sp(g); 
    sp.compute_shortest_paths();
    cout << endl; 
    cout << "average cost of all paths with graph density 0.4: " << sp.avg_path_cost() << endl;  
}   

void run_example2() 
{ 
    const int N = 50;
    Graph g(N); 
   
    GraphGenerator gen(0.2, make_pair(0, N-1)); 
    gen.generate(g);

    ShortestPath sp(g); 
    sp.compute_shortest_paths();
    cout << endl; 
    cout << "average cost of all paths with graph density 0.2: " << sp.avg_path_cost() << endl;  
}   

int main() 
{
    run_example1(); 
    run_example2();
    run_example3();
    return 0; 
}
