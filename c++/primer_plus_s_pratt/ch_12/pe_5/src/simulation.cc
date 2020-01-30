#include <cstdlib>
#include "simulation.h"

bool Simulation::createCustomer(double x)
{
    return (std::rand() * x / RAND_MAX < 1);
}