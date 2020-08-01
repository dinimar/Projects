#include "port.h"
#include <cstring>
#include <iostream>

void Port::InitCharArrays()
{
    for(size_t i=0; i<19; ++i)
        style[i]='0';

    style[19] = '\0';
}

void Port::CopyString(char * dest, const char * src)
{
    // check that length of src string
    // equal or less to length of dest string
    // not including the null terminator
    if (std::strlen(src) <= std::strlen(dest))
    {
        std::strcpy(dest, src);
    }
    else if (std::strlen(src) > std::strlen(dest))
    {
        std::strncpy(dest, src, std::strlen(dest)-1);       // copy characters
        dest[std::strlen(dest)-1] = '\0';                   // the null terminator
    }
}

Port::Port(const char * br, const char * st, int b)
{
    InitCharArrays();
    CopyString(style, st);

    brand = new char[std::strlen(br)+1];
    std::strcpy(brand, br);

    bottles = b;
}

Port::Port(const Port &p)
{
    delete[] brand;
    brand = new char[std::strlen(p.brand)+1];
    std::strcpy(brand, p.brand);

    std::strcpy(style, p.style);

    bottles = p.bottles;
}

Port & Port::operator=(const Port &p)
{
    if (this != &p)
    {
        delete[] brand;
        brand = new char[std::strlen(p.brand)+1];
        std::strcpy(brand, p.brand);

        std::strcpy(style, p.style);

        bottles = p.bottles;
    }

    return *this;
}

Port & Port::operator+=(int b)
{
    bottles += b;
}

Port & Port::operator-=(int b)
{
    bottles -= b;
}

ostream & operator<<(ostream &os, const Port &p)
{
    os << p.brand << ", " << p.style << ", " << p.bottles << std::endl;
}

void Port::Show() const
{
    std::cout << "Brand: " << brand << std::endl;
    std::cout << "Kind: " << style << std::endl;
    std::cout << "Bottles: " << bottles << std::endl;
}