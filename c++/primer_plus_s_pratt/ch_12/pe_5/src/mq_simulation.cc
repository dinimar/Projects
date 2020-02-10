#include <cstdlib>
#include <ctime>
#include <iostream>
#include "mq_simulation.h"
#include "simulation.h"

// MultiQueueSimulation::MultiQueueSimulation(int q_num = 2)
// {
//     queue_pool_ = std::vector<Queue<Customer> *>(q_num); // initialize pool
        
//         for(size_t i = 0; i < queue_pool_.size(); i++)
//         {
//             // Copy default queue from base class
//             Queue<Customer> * tmp = new Queue<Customer>(*line_);
//             // Add queue into pool
//             queue_pool_.push_back(tmp);
//         }
// }

// Frees all memory that allocated by pool
void MultiQueueSimulation::free_pool()
{
    for(size_t i = 0; i < queue_pool_.size(); i++)
    {
        delete queue_pool_.back();  // deallocate memory
        queue_pool_.pop_back();     // remove queue from pool
    }
}

// Copyies a passed pool to current object
void MultiQueueSimulation::copy_pool(const MultiQueueSimulation & ms)
{
    queue_pool_ = std::vector<Queue<Customer> *>(ms.queue_pool_.size());    // initialize pool
    
    // Add queues from passed object
    for(size_t i = 0; i < queue_pool_.size(); i++)
    {
        queue_pool_.push_back(ms.queue_pool_[i]);
    }
}

// Copy constructor
MultiQueueSimulation::MultiQueueSimulation(const MultiQueueSimulation & ms) : Simulation(ms)
{
    copy_pool(ms);
}

// Copy assignement operator
MultiQueueSimulation & MultiQueueSimulation::operator=(const MultiQueueSimulation & ms)
{
    // Check whether self-assignment or not
    if (this != &ms) {
        free_pool();
        copy_pool(ms);       
    }

    return *this;
}

// Destructor
MultiQueueSimulation::~MultiQueueSimulation()
{
    free_pool();
}

double MultiQueueSimulation::estimateAvgWaitTime(double perhour)
{
    Queue<Customer> * proc_line = nullptr;    // current processing line
    int wait_time = 0;  // time until autoteller is free
    long served = 0;    // served during the simulation
    long line_wait = 0; // cumulative time in line
    long customers = 0; // joined the queue 
    int pool_idx = 0;   // a random index for queue picking from pool 

    for (int cycle = 0; cycle < cyclelimit_; cycle++)
    {
        // change a processing queue
        pool_idx = std::rand()/((RAND_MAX + 1u)/queue_pool_.size()); 
        proc_line = queue_pool_[pool_idx];

        if (createCustomer(perhour)) // have newcomer
        {
            if (!proc_line->isfull()) 
            {
                customers++;
                temp_->set(cycle);          // cycle = time of arrival
                proc_line->enqueue(*temp_);     // add newcomer to line
            }
        }
        else if (wait_time <= 0 && !proc_line->isempty())
        {
            proc_line->dequeue(*temp_);             // attend next customer
            wait_time = temp_->ptime();             // for wait_time minutes
            line_wait += cycle - temp_->when();
            served++;

        }
        else if (wait_time > 0)
            wait_time--;

    }

    // ternary operator for preventing negative values
    return (line_wait > 0 && served > 0) ? (double)line_wait / served : -1;
}