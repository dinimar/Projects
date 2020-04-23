#include <iostream>
#include <ctime>
#include <cmath>
#include <cassert>

uint64_t modexp(uint64_t base, uint64_t exp, uint64_t modNum)
{
    while (exp != 0)
    {
        base = base * exp;
        exp--;
    }

    return base % modNum;
}

int main(int argc, char** argv)
{
    std::srand(std::time(nullptr));     // use current time as seed for random generator

    uint64_t p = 37;     // set p to 37
    uint64_t g = 5;      // set g to 5

    uint64_t a = std::rand() % 37;        // generate a, random int % 37         
    uint64_t A = modexp(g, a, p);    // generate A = (g**a) % p

    uint64_t b = std::rand() % 37;        // generate b, random int % 37         
    uint64_t B = modexp(g, b, p);    // generate B = (g**b) % p


    uint64_t sA = modexp(B, a, p);   // generate session key, s = (B**a) % p
    uint64_t sB = modexp(A, b, p);   // generate session key, s = (A**b) % p

    assert(sA == sB);

    return 0;
}