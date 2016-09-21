#include <assert.h> 

template <class To, class From> 
To safe_reinterpret_cast(From from) 
{ 
    static_assert(sizeof(From) <= sizeof(To), 
                    "reinterpret_cast not deemed safe as target type is downcasted"); 
    return reinterpret_cast<To>(from); 
}

int main()
{ 
    uint64_t a = 0;
    uint64_t* b = &a;  

    uint32_t x = reinterpret_cast<uint32_t> (b); 
    uint32_t x = safe_reinterpret_cast<uint32_t>(b); // error: compilation fails
    uint64_t y = safe_reinterpret_cast<uint64_t>(b); // success: this is a contrived example, but the point is that 8 bytes are enough to hold a pointer, while 4 bytes is not, and the first statement causes a compilation error. 

    return 0; 
} 
