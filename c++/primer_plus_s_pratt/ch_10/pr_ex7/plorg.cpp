#include "plorg.h"
#include <string>
#include <iostream>
using namespace std;

Plorg::Plorg(string name, int ci)
{
	this->name = name;
	this->ci = ci;
}

void Plorg::setCi(int ci)
{
	this->ci = ci;
}

void Plorg::report() const
{
	cout << this->name << " (" << this->ci << ")\n";
}