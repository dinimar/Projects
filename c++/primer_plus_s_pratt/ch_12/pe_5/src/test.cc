#include <iostream>
#include "uchar.h"
#include "simulation.h"

int main(int argc, char const *argv[])
{
    Simulation *sim = new Simulation(10); // set q_size_ to 10, hours_ is by default equal to 100
    // sim->estimateAvgWaitTime(15);
    for (size_t i = 0; i < 30; i++)
    {
        std::cout << "Average wait time at " << i << " perhour: " << sim->estimateAvgWaitTime(i) << std::endl;
    }

    

    return 0;
}
