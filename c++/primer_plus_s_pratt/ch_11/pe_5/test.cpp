#include "stonewt.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	Stonewt s_i(14);
	Stonewt s_f(15.0);
	Stonewt s_s(12, 4);
	
	cout << s_i << endl;
	cout << s_f << endl;
	cout << s_s << endl;

	cout << s_s + s_f << endl;
	cout << s_s - s_f << endl;
	cout << s_s * s_f << endl;
	cout << s_s / s_f << endl;

	return 0;
}