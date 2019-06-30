#include <iostream>
#include <cstring>

using namespace std;

struct CandyBar
{
	char brand[20];
	double weight;
	int calories;
};

void CandyFunc(CandyBar &bar, 
	const char *str = "Millenium Munch", double weight_ = 2.85, int cals = 350);

void DisplayCandy(const CandyBar &bar);

int main(int argc, char const *argv[])
{
	struct CandyBar bar = {"Brand", 0, 0};
	char str[4] = {'H', 'e', 'y', '\0'};

	CandyFunc(bar, str);
	DisplayCandy(bar);

	return 0;
}

void CandyFunc(CandyBar &bar, 
	const char *str, double weight_, int cals)
{
	strcpy(bar.brand, str);
	bar.weight = weight_;
	bar.calories = cals;
}

void DisplayCandy(const CandyBar &bar)
{
	cout << bar.brand << endl;
	cout << bar.weight << endl;
	cout << bar.calories << endl << endl;
}
