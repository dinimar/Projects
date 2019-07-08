#ifndef COMPLEX_0_H_
#define COMPLEX_0_H_
#include <iostream>
using std::istream;
using std::ostream; 
class complex
{
private:
	double real_part; // a real part
	double im_part; // an imaginary part
public:
	complex(double r, double i); // constructor for two args
	complex(); // default constructor
	~complex();
	
	complex operator+(const complex &s) const;
	complex operator-(const complex &s) const;
	complex operator*(const complex &s) const;
	complex operator/(const complex &s) const;
	friend complex operator*(double n, const complex &c);
	friend complex operator~(const complex &c);

	friend istream & operator>>(istream &in,  complex &c);
	friend ostream & operator<<(ostream &os, const complex &c);
};
#endif