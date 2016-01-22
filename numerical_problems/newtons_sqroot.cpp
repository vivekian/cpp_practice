// this solves section of 1.1.7 of SICP where there is a discussion of 
// computing square roots using newton ralphson method. 

#include <iostream>
#include <cmath>        // only for abs function.  

using namespace std; 

namespace {
    const double TOL = 0.01; 
}

bool IsGoodEnough(const double Guess, const int Number) 
{ 
    return (abs(((Guess * Guess) - Number)) < TOL);
}

double Average(const double a, const double b) 
{ 
    return (a + b)/2; 
}

double ImproveGuess(const double Guess, const int Number) 
{ 
    return Average(Guess, Number/Guess); 
}

double ComputeSqRoot(const double Guess, const int Number) 
{ 
    if (IsGoodEnough(Guess, Number)) 
        return Guess; 
    
    return ComputeSqRoot(ImproveGuess(Guess, Number), 
                         Number);
}
double square_root(const int Number) 
{ 
    return ComputeSqRoot(1.0, Number); 
}

int main() 
{ 
    cout << "2 " << square_root(2) << endl; 
    cout << "5 " << square_root(5) << endl; 
    cout << "10 " << square_root(10) << endl; 
    return 0; 
} 
