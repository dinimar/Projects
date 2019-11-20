// stonewt.h -- definition for the Stonewt class
#ifndef STONEWT_H_
#define STONEWT_H_
#include <iostream>
using std::ostream;
class Stonewt
{
public:
	enum Mode {STONE, I_POUNDS, F_POUNDS};
private:
	static const int Lbs_per_stn = 14; // pounds per stone
	int stone; // whole stones
	double pds_left; // fractional pounds
	double pounds; // entire weight in pounds
	Mode mode;
public:
	Stonewt(double lbs);
	// constructor for double pounds
	Stonewt(int stn, double lbs); // constructor for stone, lbs
	Stonewt();
	// default constructor
	~Stonewt();

	Stonewt operator+(const Stonewt &s) const;
	Stonewt operator-(const Stonewt &s) const;
	Stonewt operator*(const Stonewt &s) const;
	Stonewt operator/(const Stonewt &s) const;

	friend ostream & operator<<(ostream & os, const Stonewt &s);
};
#endif