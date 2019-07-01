#ifndef SALES_H
#define SALES_H
#include "sales.h"
#endif

using namespace SALES;

int main(int argc, char const *argv[])
{
	double ar[4] = {0, 1, 2, 3};

	Sales s1;
	Sales s2;

	setSales(s1, ar, 3); 
	showSales(s1);

	setSales(s2);	
	showSales(s2);

	return 0;
}