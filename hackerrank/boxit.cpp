#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int BoxesCreated,BoxesDestroyed;

class Box 
{ 
public:
    Box():l(0), b(0), h(0) 
    {
        ++BoxesCreated;
    }
    Box(long length, long breadth, long height): 
        l(length), b(breadth), h(height) 
    { 
        ++BoxesCreated; 
    } 

    ~Box() 
    { 
        ++BoxesDestroyed; 
    }

    Box(const Box& B): 
        l(B.l), b(B.b), h(B.h) 
    {
        ++BoxesCreated; 
    }

    long getLength()  { return l; }
    long getBreadth() { return b; }
    long getHeight()  { return h; }
    long long CalculateVolume() 
    { 
        return l * b * h; 
    } 

    bool operator<(Box &B) 
    { 
       if (b < B.l) 
          return true; 
       if (b < B.b && (l == B.l))
          return true; 
       if ((h < B.h) && (b == B.b) && (l == B.l))
          return true; 

       return false; 
    }  

    friend ostream& operator<<(ostream& out, const Box &B)
    {
        out << B.l << " " << B.b << " " << B.h ;
        return out; 
    } 

private: 
    long l, b, h;
};

int main() 
{ 
    Box b(1, 2, 3);
} 
