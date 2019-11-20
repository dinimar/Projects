// -std=c++11
#include <iostream>

using namespace std;

template<class T1, class T2>
auto gt(const T1 &obj1, const T2 &obj2) 
-> decltype((sizeof(obj1) > sizeof(obj2)) ? obj1 : obj2);

int main(int argc, char const *argv[])
{
	int n1 = 1010;
	double n2 = 1000.5;

	cout << gt(n1, n2) << endl;

	return 0;
}


template<class T1, class T2>
auto gt(const T1 &obj1, const T2 &obj2) 
-> decltype((sizeof(obj1) > sizeof(obj2)) ? obj1 : obj2)
{
	return (sizeof(obj1) > sizeof(obj2)) ? obj1 : obj2;
}