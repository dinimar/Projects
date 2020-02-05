#include "customer.h"
#include <cstdlib>

// Default constructor
Customer::Customer() { arrive_ = processtime_ = 0; };

// Copy constructor
Customer::Customer(const Customer & c)
{
    arrive_ = c.arrive_;
    processtime_ = c.processtime_;
}

// Copy assignment operator
Customer & Customer::operator=(const Customer & c)
{
    // Check whether self-assignment or not
    if (this != &c) 
    {
        arrive_ = c.arrive_;
        processtime_ = c.processtime_;
    } 

    return *this;
}

long Customer::when() const { return arrive_; }

int Customer::ptime() const { return processtime_; }

// customer method
// when is the time at which the customer arrives
// the arrival time is set to when and the processing
// time set to a random value in the range 1 - 3
void Customer::set(long when)
{
    processtime_ = std::rand() % 3 + 1;
    arrive_ = when;
}