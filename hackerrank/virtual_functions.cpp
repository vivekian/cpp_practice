#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

class Person 
{ 
    public: 
        Person(): name(string("")), age(0){}
        virtual void getdata() = 0; 
        virtual void putdata() = 0; 
        string name; 
        uint32_t age; 
}; 

class Professor: public Person 
{ 
    public:

       Professor(): Person()
       {
           publications = 0;
           ++pid;
           cur_id = pid; 
       }

       void getdata() 
       { 
          cin >> name >> age >> publications; 
       } 

       void putdata() 
       { 
          cout << name << " " << age << " " << publications << " " << cur_id << endl;
       } 

       static uint32_t pid; 
    private:
        uint32_t publications;
        uint32_t cur_id; 
};  

class Student: public Person 
{ 
    public:

       Student(): Person()
       {
           ++sid; 
           cur_id = sid;
       } 

       void getdata() 
       { 
          cin >> name >> age;
          for (int i=0; i<6; ++i) 
              cin >> marks[i];
       } 

       void putdata() 
       { 
          cout << name << " " << age << " " << getsum() << " " << cur_id << endl;
       } 

       static uint32_t sid; 
    private: 
        
        uint32_t marks[6];
        uint32_t cur_id; 

        uint32_t getsum() 
        {
           uint32_t sum = 0; 
           for (int i=0; i<6; ++i) 
                sum += marks[i]; 
           
           return sum; 
        }
};  
       
uint32_t Professor::pid = 1; 
uint32_t Student::sid = 1; 
int main()
{ 
    return 0; 
} 
