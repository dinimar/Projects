// randwalk.cpp -- using the Vector class
// compile with the vect.cpp file
#include <iostream>
#include <fstream>
#include <cstdlib>
// rand(), srand() prototypes
#include <ctime>
// time() prototype
#include "vect.h"

int main()
{
	using namespace std;
	using VECTOR::Vector;
	srand(time(0));
	// seed random-number generator
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;

	ofstream fout;
	fout.open("out.txt");	

	cout << "Enter target distance (q to quit): ";
	while (cin >> target)
	{
		cout << "Enter step length: ";
		fout << "Target Distance: " << target;

		if (!(cin >> dstep))
			break;

		fout << ", Step Size: " << dstep << endl;

		while (result.magval() < target)
		{
			fout << steps << ": " << result << endl;
			direction = rand() % 360;
			step.reset(dstep, direction, Vector::POL);
			result = result + step;
			steps++;
		}
		fout << steps << ": " << result << endl;

		fout << "After " << steps << " steps, the subject "
			"has the following location:\n";
		fout << result << endl;
		result.polar_mode();
		fout << " or\n" << result << endl;
		fout << "Average outward distance per step = " << result.magval()/steps << endl;
		steps = 0;

		result.reset(0.0, 0.0);
		cout << "Enter target distance (q to quit): ";
	}

	cout << "Bye!\n";
	cin.clear();
	
	while (cin.get() != '\n')
		continue;
	
	return 0;
}