#include "gunslinger.h"
#include <iostream>

void Gunslinger::Set()
{
    using std::cout;
    using std::cin;
    using std::getline;
    using std::string;

    Person::Get();
    cout << "Enter draw time: ";

    string drTime;
    getline(cin, drTime);
    mDrawTime = std::stof(drTime);
}

double Gunslinger::Draw()
{
    return mDrawTime;
}

void Gunslinger::Show()
{
    using std::cout;
    
    Person::Show();
    cout << "Draw time: " << mDrawTime << '\n';
}