// simple test to show that string literal which is const
// can't be overwritten; 

#include <cstdio> 

void test(const char *p) 
{ 
    p[0] = 'w';         // compilation fails
    printf("%s\n", p); 
}

int main() 
{ 
    const char* p = "hello"; 
    test(p); 

    return 0; 
}
