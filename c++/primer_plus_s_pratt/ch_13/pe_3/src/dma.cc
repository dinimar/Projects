// dma.cpp --dma class methods
#include "dma.h"
#include <cstring>
#include <iostream>

// ABC methods
ABC::ABC(const char *l, int r): rating(r)
{
    label = new char[std::strlen(l)+1];
    std::strcpy(label, l);
}
ABC::ABC(const ABC &rs)
{
    delete[] label;
    label = new char[std::strlen(rs.label)+1];
    std::strcpy(label, rs.label);

    rating = rs.rating;
}
ABC & ABC::operator=(const ABC &rs)
{
    if (this != &rs)
    {
        delete[] label;
        label = new char[std::strlen(rs.label)+1];
        std::strcpy(label, rs.label);

        rating = rs.rating;
    }

    return *this;
}
ABC::~ABC()
{
    delete[] label;
}
void ABC::View()
{
    std::cout << "Label: " << label << std::endl;
    std::cout << "Rating: " << rating << std::endl;
}
std::ostream & operator<<(std::ostream & os, const ABC & abc)
{
    os << "Label: " << abc.label << std::endl;
    os << "Rating: " << abc.rating << std::endl;
    return os;
}

// baseDMA methods
baseDMA::baseDMA(const char *l, int r): ABC(l, r) {}
std::ostream & operator<<(std::ostream &os, const baseDMA &rs)
{
    os << (const ABC &)rs;
    return os;
}

// lacksDMA methods
lacksDMA::lacksDMA(const char *c, const char *l, int r)
    : ABC(l, r)
{
    std::strncpy(color, c, 39);
    color[39] = '\0';
}
lacksDMA::lacksDMA(const char *c, const ABC &rs)
    : ABC(rs)
{
    std::strncpy(color, c, COL_LEN - 1);
    color[COL_LEN - 1] = '\0';
}
void lacksDMA::View()
{
    ABC::View();
    std::cout << "Color: " << color << std::endl;
}
std::ostream &operator<<(std::ostream &os, const lacksDMA &ls)
{
    os << (const ABC &)ls;
    os << "Color: " << ls.color << std::endl;
    return os;
}

// hasDMA methods
hasDMA::hasDMA(const char *s, const char *l, int r)
    : ABC(l, r)
{
    style = new char[std::strlen(s) + 1];
    std::strcpy(style, s);
}
hasDMA::hasDMA(const char *s, const ABC &rs)
    : ABC(rs)
{
    style = new char[std::strlen(s) + 1];
    std::strcpy(style, s);
}
hasDMA::hasDMA(const hasDMA &hs)
    : ABC(hs) // invoke base class copy constructor
{
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);
}
hasDMA::~hasDMA()
{
    delete[] style;
}
hasDMA &hasDMA::operator=(const hasDMA &hs)
{
    if (this != &hs)
    {
        ABC::operator=(hs); // copy base portion
        delete[] style;
        // prepare for new style
        style = new char[std::strlen(hs.style) + 1];
        std::strcpy(style, hs.style);
    }
    
    return *this;
}
void hasDMA::View()
{
    ABC::View();
    std::cout << "Style: " << style << std::endl;
}
std::ostream &operator<<(std::ostream &os, const hasDMA &hs)
{
    os << (const ABC &)hs;
    os << "Style: " << hs.style << std::endl;
    return os;
}