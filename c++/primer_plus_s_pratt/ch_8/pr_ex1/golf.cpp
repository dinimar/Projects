#ifndef GOLF_H
#define GOLF_H
#include "golf.h"
#endif

#include <cstring>
#include <iostream>

using namespace std;

void setgolf(golf &g, const char *name, int hc)
{
	strcpy(g.fullname, name);
	g.handicap = hc;
}

int setgolf(golf &g)
{
	cout << "Enter a new name\n";
	cin.get(g.fullname, Len);
	cout << "Enter a handicap\n";
	cin >> g.handicap; 
}

void handicap(golf &g, int hc)
{
	g.handicap = hc;
}

void showgolf(const golf &g)
{
	cout << g.fullname << " (" << g.handicap << ")\n";
}