#include "golf.h"
#include <cstring>
#include <iostream>

Golf::Golf()
{
	using namespace std;

	cout << "Enter a new name\n";
	cin.get(this->fullname, LEN);
	cout << "Enter a handicap\n";
	cin >> this->handicap; 
}

Golf::Golf(const char *name, int hc)
{
	using namespace std;

	strcpy(this->fullname, name);
	this->handicap = hc;
}

void Golf::Show() const
{
	using namespace std;

	cout << this->fullname << endl << this->handicap << endl << endl;
}