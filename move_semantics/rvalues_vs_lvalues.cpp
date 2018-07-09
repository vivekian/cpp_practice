// An lvalue is an expression that refers to a memory location and allows us to take the address of a memory location via the & operator. 
// An rvalue is an expression that is not a lvalue. 

void lvalue_example() 
{ 
   int a = 42; 
   int b = 26; 
//   a * b = 26; // this will never compile because rvalue on left hand side
   a = a * b; // this is ok though because a is a lvalue. 
}

void rvalue_example()
{ 
    int foobar(0); 
    int j = 0; 
    j = foobar(); // this is ok as foobar is a rvalue
}

int main()
{ 
    lvalue_example(); 
    rvalue_example(); 
    return 0; 
}
