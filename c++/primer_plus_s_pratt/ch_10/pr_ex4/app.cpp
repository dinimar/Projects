#include "sales.h"

using namespace SALES;

int main(int argc, char const *argv[])
{
	double ar[4] = {0, 1, 2, 3};

	Sales s1(ar, 3);
	Sales s2;

	s1.showSales();
	s2.showSales();

	return 0;
}