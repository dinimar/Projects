#include <iostream>
#include <uchar.h>
#include "simulation.h"
#include "queue.h"
#include "customer.h"
#include "mq_simulation.h"

int main(int argc, char const *argv[])
{   
    Simulation * sim = new Simulation(10); // set q_size_ to 10, hours_ is by default equal to 100
    std::cout << "Sinqle-queue simulation" << std::endl;
    for (size_t i = 0; i < 40; i++)
    {
        std::cout << "Average wait time at " << i << " perhour: " << sim->estimateAvgWaitTime(i) << std::endl;
    }

    MultiQueueSimulation * mqsim = new MultiQueueSimulation();  // default constructor with q_num = 2
    std::cout << "Double-queue simulation" << std::endl;
    for (size_t i = 0; i < 30; i++)
    {
        std::cout << "Average wait time at" << i << " perhour: " << mqsim->estimateAvgWaitTime(i) << std::endl;
    }

    return 0;
}
