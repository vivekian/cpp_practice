#include <string> 
#include <unistd.h> 
#include <fcntl.h>

using namespace std; 

// using posix based API calls to do read/writes.

int main()
{
    int fdw = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC); 
    int fdr = open("foo.txt", O_RDONLY); 

    write(fdw, "foo bar", 7); 
    lseek(fdw, 4, SEEK_SET);
    write(fdw, "foo", 3); 

    string buffer(7, '\0'); 
    int b = read(fdr, (void*) buffer.data(), 7); 
    assert(b == 7); 
    assert(buffer == "foo foo");

    close(fdw); 
    close(fdr); 
    return 0;  
}
