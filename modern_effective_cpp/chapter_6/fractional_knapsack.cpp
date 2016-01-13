#include <algorithm> 
#include <iostream> 
#include <vector> 

struct Item { 
    double value; 
    double size; 
    uint32_t index;
};

double fill_knapsack(std::vector<Item> items, const uint32_t maxCapacity)
{
    // sorting is done based on value/size ratio of the item
    std::sort(items.begin(), 
              items.end(), 
              [](const Item& a, const Item& b) { return (a.value/a.size) > (b.value/b.size); });

    double capacity = 0, value = 0; 
    
    for (const auto& item: items) { 
        if (capacity + item.size <= maxCapacity) { 
            capacity += item.size; 
            value += item.value; 
        } 
        else { 
            value += (maxCapacity - capacity)/item.size * item.value;
            break; 
        }
    }

    return value; 
} 

int main() 
{ 
    std::vector<Item> items = { { 10, 30, 0}, 
                                { 20, 20, 1},
                                { 30, 10, 2} };

    std::cout << fill_knapsack(items, 35) << std::endl; 
    return 0; 
}


