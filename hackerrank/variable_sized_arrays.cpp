#include <iostream> 
#include <utility> 
#include <vector> 

int main() 
{ 
    uint32_t nseqs = 0; 
    uint32_t nqueries = 0; 

    std::cin >> nseqs; 
    std::cin >> nqueries;

    std::vector<std::vector<uint32_t>> sequences(nseqs); 

    for (auto &seq: sequences) {
        uint32_t seqlength = 0;  
        std::cin >> seqlength;

        for (int i=0; i<seqlength; ++i) { 
            uint32_t element; 
            std::cin >> element; 
            seq.push_back(element);
        }
    }

    std::vector<std::pair<uint32_t, uint32_t>> queries(nqueries);

    for (uint32_t q=0; q<nqueries; ++q) { 
        uint32_t sidx, qidx; 
        std::cin >> sidx; 
        std::cin >> qidx; 
        std::pair<uint32_t,uint32_t> p(sidx, qidx);
        queries[q]=p;
    }

    for (uint32_t q=0; q<nqueries; ++q) { 
        uint32_t sidx = queries[q].first; 
        uint32_t qidx = queries[q].second;  
        std::cout << sequences.at(sidx).at(qidx) << std::endl; 
    }

    return 0; 
}  

    
