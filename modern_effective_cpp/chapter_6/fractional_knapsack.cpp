#include <algorithm> 
#include <iostream> 
#include <vector> 

struct Item { 
    float value; 
    float size; 
    uint32_t index;
};

uint32_t FillKnapsack(std::vector<Item> &Items, const uint32_t MaxCap)
{
    // sorting is done based on value/size ratio of the item
    std::sort(Items.begin(), 
              Items.end(), 
              [](const Item& A, const Item& B) { return (A.value/A.size) > (B.value/B.size); });

    float c = 0, v = 0; 
    
    for (const auto& item: Items) { 
        if (c + item.size <= MaxCap) { 
            c += item.size; 
            v += item.value; 
        } 
        else { 
            v += (MaxCap - c)/item.size * item.value;
            c = MaxCap; 
        }
        
        std::cout << "adding item " << item.index << " with value " << item.value << std::endl;
        std::cout << "c: " << c << " v: " << v << std::endl; 
       
        // since the knapsack is filled we can break out.  
        if (c >= MaxCap) 
            break;
    }

    return v; 
} 

int main() 
{ 
    std::vector<Item> items = { { 10, 30, 0}, 
                                { 20, 20, 1},
                                { 30, 10, 2} };

    std::cout << FillKnapsack(items, 35) << std::endl; 

    return 0; 
}


