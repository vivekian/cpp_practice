#include <iostream> 

int main() 
{ 
    uint32_t nseqs = 0; 
    uint32_t nqueries = 0; 

    std::cin >> nseqs; 
    std::cin >> nqueries;

    uint32_t** sequences = new uint32_t*[nseqs]; 

    for (int i=0; i<nseqs; ++i) { 
        uint32_t seqlength = 0;  
        std::cin >> seqlength;
        sequences[i] = new uint32_t[seqlength];

        for (int j=0; j<seqlength; ++j) { 
            std::cin >> sequences[i][j]; 
        }
    }

    uint32_t queries[nqueries][2]; 

    for (uint32_t q=0; q<nqueries; ++q) { 
        std::cin >> queries[q][0]; 
        std::cin >> queries[q][1]; 
    }

    for (uint32_t q=0; q<nqueries; ++q) { 
        uint32_t sidx = queries[q][0]; 
        uint32_t qidx = queries[q][1];  
        std::cout << sequences[sidx][qidx] << std::endl; 
    }

    for(int i=0; i<nseqs; ++i) { 
        delete[] sequences[i];
    } 

    delete[] sequences;

    return 0; 
}  

    
