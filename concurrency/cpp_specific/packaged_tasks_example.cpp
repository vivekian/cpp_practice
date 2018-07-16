#include <future> 
#include <iostream> 
#include <string> 
#include <vector> 

int main()
{
    std::packaged_task<int(int, int)> task([](int a, int b){return a+b;});
    std::future<int> f = task.get_future();     
    task(2,3); 
    printf("%u\n", f.get()); 

    return 0;  
}
