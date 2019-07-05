#include <iostream>
#include "vector.h"

int main(int argc, char const *argv[])
{
	using VECTOR::Vector;
	using std::cout;
	using std::endl;

	Vector v(3, 4);
	double n = v;

	cout << n << endl;

	return 0;
}