#include "move.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	using namespace std;

	Move m1(1, 1);
	Move m2(2, 2);

	cout << "m1: ";
	m1.showmove();
	cout << "m2: ";
	m2.showmove();

	cout << "m3 = m1.add(m2):\n";
	Move m3 = m1.add(m2);
	m3.showmove();

	cout << "m1.reset(0, 0):\n";
	m1.reset(0, 0);
	m1.showmove();

	return 0;
}