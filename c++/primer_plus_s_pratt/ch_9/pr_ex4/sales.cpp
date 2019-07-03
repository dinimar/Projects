#ifndef SALES_H
#define SALES_H
#include "sales.h"
#endif
#include <iostream>

using namespace std;

namespace SALES
{
	void setSales(Sales &s, const double ar[], int n)
	{	
		int count = 0;
		double max, min, ave = ar[0];

		for(int i=0;i<n and i<QUARTERS;++i)
		{
			s.sales[i] = ar[i];
			count++;

			if(max < ar[i]) max = ar[i];
			if(min > ar[i]) min = ar[i];
			ave += ar[i];
		}
		for(int i=count;i<QUARTERS;++i) s.sales[i]=0;

		ave /= QUARTERS;

		s.min = min;
		s.max = max;
		s.average = ave;
	}

	void setSales(Sales &s)
	{
		double max, min, ave = 0;

		for(int i=0;i<QUARTERS;++i)
		{
			cin >> s.sales[i];

			if(max < s.sales[i]) max = s.sales[i];
			if(min > s.sales[i]) min = s.sales[i];
			ave += s.sales[i];
		}

		ave /= QUARTERS;

		s.min = min;
		s.max = max;
		s.average = ave;
	}

	void showSales(const Sales &s)
	{
		cout << "Sales\n" << "[";

		for (int i=0;i<QUARTERS-1;++i)
		{
			cout << s.sales[i] << ", ";
		}
		cout << s.sales[3] << "]\n";

		cout << "Max: " << s.max << endl;
		cout << "Min: " << s.min << endl;
		cout << "Average: " << s.average << endl;

	}
}
