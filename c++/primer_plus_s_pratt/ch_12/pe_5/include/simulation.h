// simulation.h -- interface for a simulation
#ifndef SIMULATION_H_
#define SIMULATION_H_
#include "queue.h"
#include "customer.h"

// class for running queue simulations 
class Simulation
{
private:
    Queue<Customer> *queue_; // a queue for simulation

    enum { MIN_PER_HR = 60};

    int hours_ ; // hours of simulation
    long cyclelimit_; // # of cycles
    double perhour_; // average # of arrival per hour
    double min_per_cust_; // average time between arrivals
    long turnaways_ = 0; // turned away by full queue
    long customers_ = 0; // joined the queue 
    long served_ = 0; // served during the simulation
    long sum_line_ = 0; // cumulative line length
    int wait_time_ = 0; // time until autoteller is free
    long line_wait_ = 0; // cumulative time in line
public:
    explicit Simulation(int qs, double perhour,
                double min_per_cust,
                //  long turnaways, 
                // long customers, long served, 
                // long sum_line, int wait_time, 
                // long line_wait, 
                int hours = 100)
            : hours_(hours), cyclelimit_(MIN_PER_HR * hours_), 
            perhour_(perhour), min_per_cust_(min_per_cust)   
            // turnaways_(turnaways), customers_(customers), 
            // served_(served), sum_line_(sum_line), 
            // wait_time_(wait_time), line_wait_(line_wait) 
        {
            queue_ = new Queue<Customer>(qs);
        };
    // Customer() { arrive = processtime = 0; }
    // void set(long when);
    // long when() const { return arrive; }
    // int ptime() const { return processtime; }
    // x = average time, in minutes, between customers
// return value is true if customer shows up this minute
    // void setup();
    // create new customer
    bool createCustomer(double x);
};
#endif