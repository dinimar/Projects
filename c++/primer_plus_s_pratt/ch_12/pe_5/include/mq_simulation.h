#ifndef MQ_SIMULATION
#define MQ_SIMULATION
#include <iostream>
#include <vector>
#include "queue.h"
#include "simulation.h"

class MultiQueueSimulation: public Simulation
{
private:
    std::vector<Queue<Customer> *> queue_pool_;         // pool to store queues

    void free_pool();                                   // deallocates pool memory  
    void copy_pool(const MultiQueueSimulation & ms);    // allocates memory for pool and copies from passed object 
public:
    MultiQueueSimulation(size_t q_num = 2) : Simulation()
    {
        queue_pool_ = std::vector<Queue<Customer> *>(); // initialize pool
        queue_pool_.reserve(q_num);                      // set container's capacity

        while(queue_pool_.size() < queue_pool_.capacity()) // untill it's not full
        {
            // Copy default queue from base class
            Queue<Customer> * tmp = new Queue<Customer>(*line_);
            // Add queue into pool
            queue_pool_.push_back(tmp);
            std::cout << "new queue was added" << std::endl;
        }
    };
    // preemptive definitions to prevent public copying
    MultiQueueSimulation(const MultiQueueSimulation &s);
    MultiQueueSimulation & operator=(const MultiQueueSimulation &s);
    // Destructor
    ~MultiQueueSimulation();

    double estimateAvgWaitTime(double per_hour) override;
};

#endif