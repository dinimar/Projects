#include "sales.h"
#include <iostream>

namespace SALES
{
	Sales::Sales(const double ar[], int n)
	{	
		int count = 0;
		double max, min, ave = ar[0];

		for(int i=0;i<n and i<QUARTERS;++i)
		{
			this->sales[i] = ar[i];
			count++;

			if(max < ar[i]) max = ar[i];
			if(min > ar[i]) min = ar[i];
			ave += ar[i];
		}
		for(int i=count;i<QUARTERS;++i) this->sales[i]=0;

		ave /= QUARTERS;

		this->min = min;
		this->max = max;
		this->average = ave;
	}

	Sales::Sales()
	{
		using namespace std;

		double max, min, ave = 0;

		for(int i=0;i<QUARTERS;++i)
		{
			cin >> this->sales[i];

			if(max < this->sales[i]) max = this->sales[i];
			if(min > this->sales[i]) min = this->sales[i];
			ave += this->sales[i];
		}

		ave /= QUARTERS;

		this->min = min;
		this->max = max;
		this->average = ave;
	}

	void Sales::showSales() const
	{
		using namespace std;

		cout << "Sales\n" << "[";

		for (int i=0;i<QUARTERS-1;++i)
		{
			cout << this->sales[i] << ", ";
		}
		cout << this->sales[3] << "]\n";

		cout << "Max: " << this->max << endl;
		cout << "Min: " << this->min << endl;
		cout << "Average: " << this->average << endl;
	}
}
