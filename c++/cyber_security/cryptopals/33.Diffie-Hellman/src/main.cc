#include <iostream>
#include <ctime>
#include <cmath>
#include <cassert>

int main(int argc, char** argv)
{
    std::srand(std::time(nullptr));     // use current time as seed for random generator

    int p = 37;     // set p to 37
    int g = 5;      // set g to 5

    int a = std::rand() % 37;        // generate a, random int % 37         
    int A = int(std::pow(double(g), double(a))) % p;    // generate A = (g**a) % p

    int b = std::rand() % 37;        // generate b, random int % 37         
    int B = int(std::pow(double(g), double(b))) % p;    // generate B = (g**b) % p


    int sA = int(std::pow(double(B), double(a))) % p;   // generate session key, s = (B**a) % p
    int sB = int(std::pow(double(A), double(b))) % p; 

    assert(sA == sB);

    return 0;
}