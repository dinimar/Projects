#include <iostream>
#include <uchar.h>
#include "simulation.h"
#include "queue.h"
#include "customer.h"
// #include "mq_simulation.h"

int main(int argc, char const *argv[])
{
    Queue<Customer> * queue = new Queue<Customer>();
    // Initialize queue
    std::cout << "Original Queue elements that written:" << std::endl;
    while (!queue->isfull())
    {
        Customer * cust = new Customer(); 
        cust->set(queue->queuecount());
        queue->enqueue(*cust);

        std::cout << cust->when() << ", ";
    }
    // std::cout << std::endl;
    // // Read original queue
    Customer tmp;
    // std::cout << std::endl << "Original Queue elements that read:" << std::endl;
    // while (!queue->isempty())
    // {
    //     queue->dequeue(tmp);
    //     std::cout << tmp.when() << ", ";
    // }
    // std::cout << std::endl;
    
    
    // // Read copy queue
    Queue<Customer> * copy = new Queue<Customer>(*queue);
    // Customer * tmp = new Customer();
    std::cout <<  std::endl << "Copy Queue elements that read:" << std::endl;
    // // std::cout << copy->isempty() << std::endl;
    while (!copy->isempty())
    {   
        copy->dequeue(tmp);
        std::cout << tmp.when() <<", ";
    }
    
    // Queue<Customer> copy(*queue);
    // Simulation * sim = new Simulation(10); // set q_size_ to 10, hours_ is by default equal to 100
    // std::cout << "Sinqle-queue simulation" << std::endl;
    // for (size_t i = 0; i < 30; i++)
    // {
    //     std::cout << "Average wait time at " << i << " perhour: " << sim->estimateAvgWaitTime(i) << std::endl;
    // }

    // MultiQueueSimulation * mqsim = new MultiQueueSimulation();
    // std::cout << "Double-queue simulation" << std::endl;
    // for (size_t i = 0; i < 30; i++)
    // {
    //     std::cout << "Average wait time at" << i << " perhour: " << mqsim->estimateAvgWaitTime(i) << std::endl;
    // }

    return 0;
}
