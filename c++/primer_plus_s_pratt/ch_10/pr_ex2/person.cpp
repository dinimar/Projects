#include "person.h"
#include <iostream>
#include <cstring>

Person::Person()
{ 
	this->lname = ""; 
	this->fname[0] = '\0';
}

Person::Person(const string &ln, const char *fn)
{
	this->lname = ln;
	strcpy(this->fname, fn);
}

void Person::Show() const
{
	using namespace std;
	cout << this->fname << " " << this->lname << endl;
}

void Person::FormalShow() const
{
	using namespace std;
	cout << this->lname << " " << this->fname << endl;
}