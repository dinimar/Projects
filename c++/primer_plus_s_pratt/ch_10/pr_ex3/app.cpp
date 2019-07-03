#include "golf.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	std::cout << "\nGolf(const char * name, int hc):\n";
	Golf g1 = Golf("Boris Becker", 100);
	g1.Show();

	std::cout << "\nGolf():\n";
	Golf g2;
	g2.Show();

	return 0;
}