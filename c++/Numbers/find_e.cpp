#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdlib.h> 

int main(int argc, char const *argv[])
{
	std::cout << std::setprecision(atoi(argv[1])) << M_E << std::endl;

	return 0;
}