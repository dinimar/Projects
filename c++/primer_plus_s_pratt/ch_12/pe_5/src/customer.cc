#include "customer.h"
#include <cstdlib>

Customer::Customer() { arrive_ = processtime_ = 0; };
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