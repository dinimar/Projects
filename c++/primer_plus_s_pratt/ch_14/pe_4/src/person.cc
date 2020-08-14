#include "person.h"
#include <iostream>

using std::cout;
using std::cin;
using std::getline;

void Person::Get()
{
    cout << "Enter a first name: ";
    getline(cin, mFirstName);
    cout << "Enter a second name: ";
    getline(cin, mLastName);
}

void Person::Show()
{
    cout << "Name: " << mFirstName << " " << mLastName << '\n';
}