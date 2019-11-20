#ifndef GOLF_H
#define GOLF_H
#include "golf.h"
#include <iostream>
#endif

int main(int argc, char const *argv[])
{
	golf g = {"Name", 50};
	showgolf(g);


	std::cout << "\nvoid setgolf():\n";
	setgolf(g, "Boris Becker", 100);
	showgolf(g);

	std::cout << "\nint setgolf():\n";
	setgolf(g);
	showgolf(g);

	std::cout << "\nvoid handicap():\n";
	handicap(g, 34);
	showgolf(g);

	return 0;
}