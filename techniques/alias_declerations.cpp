#include <string> 
#include <vector> 
#include <iostream> 

int main() 
{ 
    // simple example of alias declerations 
    using VecStr = std::vector<std::string>;
    VecStr vNames = {"amy", "ben", "cathy", "derick", "emily"}; 

    for(auto name:vNames) 
        std::cout << name << std::endl; 

    return 0; 
}
