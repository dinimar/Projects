#include "person.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	using namespace std;

	Person one;
	one.Show();
	one.FormalShow();
	cout << endl;

	Person two("Smythecraft");
	two.Show();
	two.FormalShow();
	cout << endl;

	Person three("Dimwiddy", "Sam");
	three.Show();
	three.FormalShow();

	return 0;
}