// simulation.h -- interface for a simulation
#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <cstdlib>
#include <ctime>
#include "queue.h"
#include "customer.h"

// class for running queue simulations
class Simulation
{
private:
    Queue<Customer> * line_; // a queue for simulation
    Customer * temp_;

    enum { MIN_PER_HR = 60 };

    int hours_ ; // hours of simulation
    long cyclelimit_; // # of cycles
    // double perhour_; 
public:
    explicit Simulation(int qs = 10,
                //  long turnaways, 
                // long customers, long served, 
                // long sum_line, int wait_time, 
                // long line_wait, 
                int hours = 100)
            : hours_(hours), cyclelimit_(MIN_PER_HR * hours_)
            // turnaways_(turnaways), customers_(customers), 
            // served_(served), sum_line_(sum_line), 
            // wait_time_(wait_time), line_wait_(line_wait) 
        {
            line_ = new Queue<Customer>(qs);
            temp_ = new Customer();
            std::srand(std::time(0));
        };

    // preemptive definitions to prevent public copying
    Simulation(const Simulation &s);
    Simulation &operator=(const Simulation &s);
    
    // perhour = average # of arrival per hour
    // return average wait time
    double estimateAvgWaitTime(double perhour); // run simulation

    // x = average time, in minutes, between customers
    // return value is true if customer shows up this minute
    bool createCustomer(double x);

    ~Simulation();
};

#endif