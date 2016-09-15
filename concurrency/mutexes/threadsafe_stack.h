// this implementation is copied from listing 3.4 from C++ concurrency in Action

#include <exception> 
#include <memory> 
#include <mutex> 
#include <stack> 

// exception in case stack is empty 
struct empty_stack: std::exception 
{
    const char* what() const throw(); 
}; 

// generic stack class 
template<typename T>
class threadsafe_stack 
{ 

    private: 
        std::stack<T> data;     // encapsulate over the stl stack object. 
        mutable std::mutex m;   // mutex to protect the 'data' object
                                // notice how its mutable since empty() is a const method 
                                // this is a typical use case for mutable to differentiate between 
                                // logical and bitwise constness. 

    public:
        threadsafe_stack() {}
        
        threadsafe_stack(const threadsafe_stack& other) // const constructor 
        {
            // the mutex is locked to ensure that the copy goes through correctly.
            std::lock_guard<std::mutex> lock(m); 
            data = other.data; 
        }

        threadsafe_stack& operator=(const threadsafe_stack&) = delete; 

        void push(T new_value)
        { 
            std::lock_guard<std::mutex> lock(m); 
            data.push(new_value); 
        }

        // this pop operation prevents end client from calling top() and pop() seperately 
        std::shared_ptr<T> pop() 
        { 
            std::lock_guard<std::mutex> lock(m); 
            if (data.empty()) throw empty_stack(); 

            // allocate return value before popping. 
            std::shared_ptr<T> const ret(std::make_shared<T>(data.top()));
            data.pop(); 

            return ret; 
        }

        void pop(T& value)
        {
            std::lock_guard<std::mutex> lock(m); 
            if (data.empty()) throw empty_stack(); 

            value = data.top(); 
            data.pop(); 
        }

        bool empty() const 
        { 
            std::lock_guard<std::mutex> lock(m); 
            return data.empty(); 
        }
}; 

