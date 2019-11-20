// -std=c++11
#include <iostream>

int main(int argc, char const *argv[])
{
	std::cout << atof(argv[1]) * atof(argv[2]) * atof(argv[3]) << std::endl;
	return 0;
}