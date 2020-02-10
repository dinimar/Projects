#include <cstdlib>
#include <iostream>
#include "simulation.h"

// Copy constructor
Simulation::Simulation(const Simulation &s)
{
    // allocate memory
    line_ = new Queue<Customer>();
    temp_ = new Customer();
    // copy pointer values using copy assignment operator
    *line_ = *(s.line_);
    *temp_ = *(s.temp_);
}

// Copy assignment operator
Simulation & Simulation::operator=(const Simulation &s)
{
    // Check whether self-assignment or not
    if (this != &s) {
        // copy primitives
        hours_ = s.hours_;
        cyclelimit_ = s.cyclelimit_;
        // deallocate memory
        delete line_;
        delete temp_;
        // allocate memory
        line_ = new Queue<Customer>();
        temp_ = new Customer();
        // copy pointer values using copy assignment operator
        *line_ = *(s.line_);
        *temp_ = *(s.temp_);
    }

    return *this;
};

// 
double Simulation::estimateAvgWaitTime(double perhour)
{
    int wait_time = 0; // time until autoteller is free
    long served = 0; // served during the simulation
    long line_wait = 0; // cumulative time in line
    long customers = 0; // joined the queue 

    for (int cycle = 0; cycle < cyclelimit_; cycle++)
    {
        if (createCustomer(perhour)) // have newcomer
        {
            if (!line_->isfull()) 
            {
                customers++;
                temp_->set(cycle);          // cycle = time of arrival
                line_->enqueue(*temp_);     // add newcomer to line
            }
        }
        else if (wait_time <= 0 && !line_->isempty())
        {
            line_->dequeue(*temp_);             // attend next customer
            wait_time = temp_->ptime();         // for wait_time minutes
            line_wait += cycle - temp_->when();
            served++;

        }
        else if (wait_time > 0)
            wait_time--;

    }

    // ternary operator for preventing negative values
    return (line_wait > 0 && served > 0) ? (double)line_wait / served : -1;
}

// Checks whether new customer has come or not
bool Simulation::createCustomer(double x)
{
    return (std::rand() * x / RAND_MAX < 1);
}

// Destructor
Simulation::~Simulation()
{
    delete line_;
    delete temp_;
}