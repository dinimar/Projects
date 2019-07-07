// randwalk.cpp -- using the Vector class
// compile with the vect.cpp file
#include <iostream>
#include <cstdlib>
// rand(), srand() prototypes
#include <ctime>
// time() prototype
#include "vector.h"

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
	int n;
	int high;
	int low;
	double ave;

		cout << "Enter target distance (q to quit): ";
		while (cin >> target)
		{
			cout << "Enter step length: ";
			if (!(cin >> dstep))
				break;

		cout << "Enter number of attempts: ";
		cin >> n;


		for(int i=0;i<n;i++)
		{
			while (result.magval() < target)
			{
				direction = rand() % 360;
				step.reset(dstep, direction, Vector::POL);
				result = result + step;
				steps++;
			}
			
			if (steps > high) high = steps;
			if (steps < low or low==0) low = steps;

			// cout << "After " << steps << " steps, the subject "
			// "has the following location:\n";
			// cout << result << endl;
			result.polar_mode();
			// cout << " or\n" << result << endl;
			// cout << "Average outward distance per step = "
			// << result.magval()/steps << endl;
			steps = 0;
			result.reset(0.0, 0.0);

		}
			cout << "High: " << high << endl;
			cout << "Low: " << low << endl;
			cout << "Average: " << (high + low) / 2.0  << endl;
			cout << "Enter target distance (q to quit): ";
		}

	
	cout << "Bye!\n";
	cin.clear();
	while (cin.get() != '\n')
	continue;
	return 0;
}