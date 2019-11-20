#include "stonewt.h"

int main(int argc, char const *argv[])
{
	Stonewt st1(10, 8);

	Stonewt res = operator*(2, st1);
	res.show_stn();	

	return 0;
}