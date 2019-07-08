// stonewt.cpp -- Stonewt methods
#include <iostream>
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
#include "complex0.h"

complex::complex(double r, double i)
{
	real_part = r;
	im_part = i;
}
// default constructor
complex::complex()
{
	real_part = 0;
	im_part = 0;
}
complex::~complex(){}

// arithmetic operators
complex complex::operator+(const complex &c) const
{
	return complex(real_part+c.real_part, im_part+c.im_part);
}

complex complex::operator-(const complex &c) const
{
	return complex(real_part-c.real_part, im_part-c.im_part);
}

complex complex::operator*(const complex &c) const
{
	// TODO: fix calculation
	return complex((real_part*c.real_part + im_part*c.im_part),
					(real_part*c.im_part + im_part*c.real_part));
}

complex operator*(double n, const complex &c)
{
	return complex(c.real_part*n, c.im_part*n);
}

complex complex::operator/(const complex &c) const
{
	double div = c.real_part*c.real_part - c.im_part*c.im_part;

	// TODO: fix calculation
	return complex((real_part*c.real_part + im_part*c.im_part)/div, 
					(im_part+c.im_part)/div);
}

complex operator~(const complex &c)
{
	return complex(c.real_part, -c.im_part);
}

istream & operator>>(istream &in,  complex &c) 
{ 
    cout << "real: "; 
    in >> c.real_part; 
    cout << "imaginary: "; 
    in >> c.im_part; 
    return in; 
}

ostream & operator<<(ostream &os, const complex &c)
{
	os << "(" << c.real_part << ", " << c.im_part << "i)"; 
    return os; 	
}