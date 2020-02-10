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
protected:
    Queue<Customer> * line_;    // a queue for simulation
    Customer * temp_;           // a temporary customer object for line_ modifying

    enum { MIN_PER_HR = 60 }; // const value

    int hours_ ;        // hours of simulation
    long cyclelimit_;   // # of cycles
public:
    explicit Simulation(int qs = 10, int hours = 100)
            : hours_(hours), cyclelimit_(MIN_PER_HR * hours_)
        {
            line_ = new Queue<Customer>(qs);
            temp_ = new Customer();
            std::srand(std::time(0)); // init srand by current time
        };

    // preemptive definitions to prevent public copying
    Simulation(const Simulation &s);
    Simulation &operator=(const Simulation &s);
    
    // perhour = average # of arrival per hour
    // Runs simulation and returns average wait time
    virtual double estimateAvgWaitTime(double perhour);

    // x = average time, in minutes, between customers
    // Checks whether new customer has come or not
    // returns value is true if customer shows up this minute
    virtual bool createCustomer(double x);

    // Destructor
    virtual ~Simulation();
};

#endif