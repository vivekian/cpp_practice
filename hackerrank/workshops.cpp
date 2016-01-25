#include <algorithm> 

struct Workshop 
{ 
    int start_time; 
    int duration; 
    int end_time; 
}; 

struct AvailableWorkshops
{ 
    struct Workshop* wlist; 
    int N; 
}; 

struct AvailableWorkshops* initialize(int StarTimes[], int Durations[], const int N)
{ 
    struct AvailableWorkshops* tmp = new AvailableWorkshops; 
    tmp->wlist = new Workshop[N];
    tmp->N = N; 

    for (int i=0; i<N; ++i) { 
        tmp->wlist[i].start_time = StarTimes[i]; 
        tmp->wlist[i].duration =  Durations[i]; 
        tmp->wlist[i].end_time = StarTimes[i] + Durations[i];
    }

    return tmp;
}

int CalculateMaxWorkshops(AvailableWorkshops *ptr) 
{ 
    std::sort(ptr->wlist[0], 
              ptr->wlist[(ptr->N)-1], 
              [](const auto &A, const auto &B) { A.duration < B.duration; })

    return 0; 
}

int main() 
{ 
    return 0; 
} 
