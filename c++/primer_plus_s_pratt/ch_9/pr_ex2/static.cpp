// static.cpp -- using a static local variable
#include <iostream>
#include <cstring>
// function prototype
void strcount(std::string str);

int main()
{
	using namespace std;
	string str = "";
	char next = '0';

	cout << "Enter a line:\n";
	
	
	cin.get(next);	
	while (next != '\n') 
	{
		str.insert(str.end(), next);
		cin.get(next);
	}	
	strcount(str);

	while(str.compare("")) 
	{
		str = "";
		cout << "Next string(empty line to quit):\n";
		
		cin.get(next);	 
		while (next != '\n') 
		{
			str.insert(str.end(), next);
			cin.get(next);	
		}	
		strcount(str);
	}

	cout << "Bye\n";
	return 0;
}

void strcount(const std::string str)
{
	using namespace std;
	cout << "\"" << str <<"\" contains ";

	cout << str.size() << " characters\n";
	cout << str.length() << " characters total\n\n";
}