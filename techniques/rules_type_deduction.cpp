#include <cstdio>

template<typename T>
void foo(const T& x)
{
    puts(__PRETTY_FUNCTION__);
}

int main()
{
    foo(4);
    foo(4.2);
    foo("hello");
}



