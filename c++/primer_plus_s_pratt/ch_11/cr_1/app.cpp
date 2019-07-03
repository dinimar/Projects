#include "stonewt.h"

int main(int argc, char const *argv[])
{
	Stonewt st1(10, 8);
	Stonewt st2(21, 2);

	Stonewt res = st1.operator*(2);
	res.show_stn();

	res = st2.operator*(2);
	res.show_stn();

	return 0;
}