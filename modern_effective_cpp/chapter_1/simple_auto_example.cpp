#include <iostream> 
#include <map> 
#include <string> 

int main()
{ 
    std::map<std::string, uint32_t> m; 
    std::map<std::string, uint32_t>::iterator i = m.begin();

    auto j = m.begin();

    return 0;
} 
