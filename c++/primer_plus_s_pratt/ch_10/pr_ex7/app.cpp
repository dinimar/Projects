#include "plorg.h"

int main(int argc, char const *argv[])
{
	Plorg p;
	p.report();

	p.setCi(100);
	p.report();
	
	return 0;
}