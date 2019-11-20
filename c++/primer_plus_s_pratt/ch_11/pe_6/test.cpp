#include <iostream>
#include <stonewt.h>

using namespace std;

int main(int argc, char const *argv[])
{	
	Stonewt st_a[6] = {Stonewt(11), Stonewt(14.3), Stonewt(13)};
	double tmp = 0;

	Stonewt max(0);
	Stonewt min(0);
	Stonewt zero(0);
	Stonewt st11(11);
	int high11 = 0;
	int low11 = 0;
	int eq11 = 0;

	for(int i=0;i<6;i++)
	{
		if(i>2)
		{
			cin >> tmp;
			st_a[i] = Stonewt(tmp);
		}

		max = max < st_a[i] ? st_a[i] : max;
		min = (min > st_a[i] or min == zero) ? st_a[i] : min;

		high11 = st_a[i] > st11 ? (high11 + 1) : high11;
		low11 = st_a[i] < st11 ? (low11 + 1) : low11;
		eq11 = st_a[i] == st11 ? (eq11 + 1) : eq11;
	}

	cout << "Max:\n" << max << endl;
	cout << "Min:\n" << min << endl;
	// cout << "Average:\n" << Stonewt((max.pounds+min.pounds)/2.0) << endl << endl;

	cout << "Higher than 11 = " << high11 << endl;
	cout << "Lower than 11 = " << low11 << endl;
	cout << "Equal than 11 = " << eq11 << endl;

	return 0;
}