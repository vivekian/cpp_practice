#include <iostream> 
#include <mutex> 
#include <thread> 
using namespace std; 

struct Node { 
    Node(int in): data(in), next(nullptr) {}
    int data; 
    Node* next; 
}; 

class LinkedList 
{
    public: 
        LinkedList():head(nullptr),tail(nullptr) 
        {} 

        ~LinkedList() 
        { 
            auto tmp = head; 

            while (tmp) { 
                auto nxt = tmp->next; 
                delete tmp; 
                tmp = nxt; 
            } 
        }

        void insert(int input) 
        {
            lock_guard<mutex> lock(m);
            if (!head) { 
               head = new Node(input); 
               tail = head; 
            } 
            else {  
                tail->next = new Node(input); 
                tail = tail->next; 
            }
        }

        void write(ostream& os) 
        { 
            auto tmp = head; 
            
            while (tmp) { 
                os << tmp->data << "->"; 
                tmp = tmp->next; 
            } 
            
            os << "\n"; 
        }

    private: 
        Node* head; 
        Node* tail; 
        mutex m; 
};

namespace { 
    LinkedList ll;
} 

void thread_a()
{ 
    for (int i=0; i<10; ++i) { 
        ll.insert(i); 
    } 
}

void thread_b() 
{ 
    for (int i=10; i<20; ++i) { 
        ll.insert(i); 
    }
}

int main()
{
    thread a (thread_a); 
    thread b (thread_b); 

    a.join(); 
    b.join(); 

    ll.write(cout); 
    return 0; 
} 
