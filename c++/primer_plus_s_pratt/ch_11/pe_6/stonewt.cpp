// stonewt.cpp -- Stonewt methods
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
#include "stonewt.h"
// construct Stonewt object from double value
Stonewt::Stonewt(double lbs)
{
	stone = int (lbs) / Lbs_per_stn;
	// integer division
	pds_left = int (lbs) % Lbs_per_stn + lbs - int(lbs);
	pounds = lbs;
}
// construct Stonewt object from stone, double values
Stonewt::Stonewt(int stn, double lbs)
{
	stone = stn;
	pds_left = lbs;
	pounds = stn * Lbs_per_stn +lbs;
}
Stonewt::Stonewt()
// default constructor, wt = 0
{
	stone = pounds = pds_left = 0;
}
Stonewt::~Stonewt(){}
// destructorAutomatic Conversions and Type Casts for Classes
// show weight in stones
void Stonewt::show_stn() const
{
	cout << stone << " stone, " << pds_left << " pounds\n";
}
// show weight in pounds
void Stonewt::show_lbs() const
{
	cout << pounds << " pounds\n";
}

bool Stonewt::operator==(const Stonewt &rhs) const
{
	return pounds == rhs.pounds;
}

bool Stonewt::operator!=(const Stonewt &rhs) const
{
	return pounds != rhs.pounds;
}

bool Stonewt::operator<(const Stonewt &rhs) const
{
	return pounds < rhs.pounds;
}

bool Stonewt::operator>(const Stonewt &rhs) const
{
	return pounds > rhs.pounds;
}

bool Stonewt::operator>=(const Stonewt &rhs) const
{
	return pounds >= rhs.pounds;
}

bool Stonewt::operator<=(const Stonewt &rhs) const
{
	return pounds <= rhs.pounds;
}

ostream & operator<<(ostream &os, const Stonewt &s)
{
	// switch(s.mode)
	// {
	// 	case Stonewt::STONE:
			os << "Stones: " << s.stone << "\nPounds: "
			<< s.pounds << "\nPounds left: " << s.pds_left << endl;
			// break;?
		// case Stonewt::I_POUNDS:
		// 	os << "I_POUNDS mode: \nStones: " << s.stone << "\nPounds: "
		// 	<< s.pounds << "\nNo pounds left\n";
		// 	break;
		// case Stonewt::F_POUNDS:
		// 	os << "F_POUNDS mode: \nStones: " << s.stone << "\nPounds: "
		// 	<< s.pounds << "\nPounds left: " << s.pds_left << endl;  
		// 	break;
// 	}

	return os;
}