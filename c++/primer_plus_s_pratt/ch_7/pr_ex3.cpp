#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

void ConvertToUC(const string &str);

int main(int argc, char const *argv[])
{
	string str = "";
	cout << "Enter a string(q to quit): ";
	cin >> str;	

	while(strcmp(str.c_str(), "q")){
		ConvertToUC(str);
		cout << "Next string(q to quit): ";

		cin >> str;
	}
	cout << "Bye.\n";

	return 0;
}

void ConvertToUC(const string &str) {
	cout << "Converted string: ";
	for(int i=0; i<str.length(); i++) 
		cout << (char)toupper(str[i]);
	cout << endl;
}