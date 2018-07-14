#include <algorithm> 
#include <string> 

using namespace std;

void reverse_words_in_place(string& s) 
{
    std::reverse(s.begin(), s.end()); 

    for (auto it=s.begin(); true; ++it) { 
        auto next = find(it, s.end(), ' '); 
        std::reverse(it, next); 

        if (next == s.end()) { 
            break;
        }

        it = next; 
    }
}


using namespace std; 

int main()
{
    string s = "the big wolf jumped over the fence";
    reverse_words_in_place(s); 
    printf("%s\n", s.c_str()); 
    return 0;  
}
