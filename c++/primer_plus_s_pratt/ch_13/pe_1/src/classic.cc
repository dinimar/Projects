#include "classic.h"
#include <cstring>
#include <iostream>

Classic::Classic() : Cd()
{
    primaryWork = new char[11];
    std::strcpy(primaryWork, "No primary");
}

Classic::Classic(char * prW, char * s1, char * s2, int n, double x) : Cd(s1, s2, n, x)
{
    primaryWork = new char[std::strlen(prW) + 1];
    std::strcpy(primaryWork, prW);
}

Classic::~Classic()
{
    delete[] primaryWork;
}

Classic::Classic(const Classic & cl): Cd(cl)
{
    delete[] primaryWork;
    
    primaryWork = new char[std::strlen(cl.primaryWork) + 1];
    std::strcpy(primaryWork, cl.primaryWork);
}

Classic & Classic::operator=(const Classic & cl)
{
    if (this != &cl)
    {
        Cd::operator=(cl);

        delete[] primaryWork;
    
        primaryWork = new char[std::strlen(cl.primaryWork) + 1];
        std::strcpy(primaryWork, cl.primaryWork);
    }

    return *this;
}

void Classic::Report() const
{
    std::cout << "Primary Work: " << primaryWork << std::endl;
    Cd::Report();
}