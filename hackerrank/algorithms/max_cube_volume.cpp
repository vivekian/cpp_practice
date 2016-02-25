#include <algorithm> 
#include <vector>
#include <cstdio> 
#include <stdint.h> 

int max_cube_vol(const int n) 
{ 
    if (n <= 2) 
        return 0; 

    uint32_t maxvalue = 1; 

    for (uint32_t b=1; b<=n/2; ++b) { 
       
       uint32_t w = 1; 
       uint32_t h = n - b - w; 

       while (w < h) { 
            maxvalue = std::max(maxvalue, b * w * h); 
            ++w; 
            --h; 
       }
    }

    return maxvalue; 
}

int main() 
{ 
    std::vector<uint32_t> tests = {5, 6, 7, 8, 100, 0, 100000}; 
    
    for (auto test: tests) 
    { 
        printf("%6u: %u\n", test, max_cube_vol(test));
    }
    
    return 0; 
}
