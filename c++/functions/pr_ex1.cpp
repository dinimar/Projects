#include <iostream>

using namespace std;
int count = 1;

void PrintStr(const string *str, int n = 0);

int main(int argc, char const *argv[])
{
	string *str = new string("HA-HA");
	
	PrintStr(str);
	PrintStr(str, 1);
	PrintStr(str);
	PrintStr(str, 1);

	return 0;
}

void PrintStr(const string *str, int n)
{
	if (n == 0) {
		cout << *str << endl;
	} else {
		for(int i = 0; i < count; i++) {
			cout << *str << endl;
		}
	}

	cout << endl;
	count++;
}