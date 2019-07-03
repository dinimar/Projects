#include <iostream>
#include <string>

using namespace std;

void iquote(int arg);
void iquote(double arg);
void iquote(string arg);

int main(int argc, char const *argv[])
{
	iquote(1);
	iquote(1.5);
	iquote("string");

	return 0;
}

void iquote(int arg)
{
	cout << "Int arg: " << arg << endl;
}

void iquote(double arg)
{
	cout << "Double arg: " << arg << endl;
}

void iquote(string arg)
{
	cout << "String arg: " << arg << endl;
}