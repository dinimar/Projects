// stonewt.cpp -- Stonewt methods
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
#include "stonewt.h"
// construct Stonewt object from double value
Stonewt::Stonewt(double lbs)
{
	stone = int (lbs) / Lbs_per_stn; // integer division
	pds_left = int (lbs) % Lbs_per_stn + lbs - int(lbs);
	pounds = lbs;
	
	mode = (pds_left == 0) ? Stonewt::I_POUNDS : Stonewt::F_POUNDS;
}

// construct Stonewt object from stone, double values
Stonewt::Stonewt(int stn, double lbs)
{
	stone = stn;
	pds_left = lbs;
	pounds = stn * Lbs_per_stn +lbs;
	mode = Stonewt::STONE;
}

Stonewt::Stonewt()
// default constructor, wt = 0
{
	stone = pounds = pds_left = 0;
}

Stonewt::~Stonewt(){}// destructor

Stonewt Stonewt::operator+(const Stonewt &s) const
{
	return Stonewt(pounds + s.pounds);
}

Stonewt Stonewt::operator-(const Stonewt &s) const
{
	return Stonewt(pounds - s.pounds);
}

Stonewt Stonewt::operator*(const Stonewt &s) const
{
	return Stonewt(pounds * s.pounds);
}

Stonewt Stonewt::operator/(const Stonewt &s) const
{
	return Stonewt(pounds / s.pounds);
}

ostream & operator<<(ostream &os, const Stonewt &s)
{
	switch(s.mode)
	{
		case Stonewt::STONE:
			os << "STONE mode: \nStones: " << s.stone << "\nPounds: "
			<< s.pounds << "\nPounds left: " << s.pds_left << endl;
			break;
		case Stonewt::I_POUNDS:
			os << "I_POUNDS mode: \nStones: " << s.stone << "\nPounds: "
			<< s.pounds << "\nNo pounds left\n";
			break;
		case Stonewt::F_POUNDS:
			os << "F_POUNDS mode: \nStones: " << s.stone << "\nPounds: "
			<< s.pounds << "\nPounds left: " << s.pds_left << endl;  
			break;
	}

	return os;
}