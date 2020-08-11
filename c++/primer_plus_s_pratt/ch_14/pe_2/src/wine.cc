#include "wine.h"

Wine::Wine(const char * l, int y, const int yr[], const int bot[]): 
string(l), PairArray(std::valarray<int>(yr, y), std::valarray<int>(bot, y))
{}

Wine::Wine(const char * l, int y):
string(l), PairArray(std::valarray<int>(y), std::valarray<int>(y))
{}

void Wine::GetBottles()
{
    using std::cout;
    using std::cin;
    // using std::string;

    cout << "Enter " << (const string &)(*this) << "data for " << PairArray::first().size() << " year(s):\n";

    for(size_t i=0; i<PairArray::first().size(); ++i)
    {
        cout << "Enter year: ";
        cin >> PairArray::first()[i];     // init year
        cout << "Enter bottles for that year: ";
        cin >> PairArray::second()[i];    // init number of bottles
    }
}

std::string & Wine::Label()
{
    return (string &)(*this);
}

void Wine::Show()
{
    using std::cout;
    cout << "Wine: " << (const string &)(*this) << '\n'
         << "\t\tYear\t\tBottles\n";
    for(size_t i=0; i<PairArray::first().size(); ++i)
    {
        cout << "\t\t" << PairArray::first()[i] << "\t\t" << PairArray::second()[i] << '\n';
    }  
}

int Wine::sum()
{
    return PairArray::second().sum();
}
