#include <iostream>
#include <cstring> // for strlen(), strcpy()

using namespace std;

struct stringy {
	char *str; // points to a string
	int ct; // length of string (not counting '\0')
};

void set(stringy &, const char *);
void show(const stringy &, int n=1);
void show(const char *, int n=1);

// prototypes for set(), show(), and show() go here
int main()
{
	stringy beany;
	char testing[] = "Reality isn't what it used to be.";

	set(beany, testing); // first argument is a reference,
				// allocates space to hold copy of testing,
				// sets str member of beany to point to the
				// new block, copies testing to new block,
				// and sets ct member of beany
	show(beany); // prints member string once
	show(beany, 2); // prints member string twice
	testing[0] = 'D';
	testing[1] = 'u';
	show(testing); // prints testing string once
	show(testing, 3); // prints testing string thrice
	show("Done!");
	
	return 0;
}

void set(stringy &stringy_, const char *tmp)
{
	stringy_.ct = strlen(tmp);
	stringy_.str = new char[stringy_.ct+1];
	strcpy(stringy_.str, tmp);
}

void show(const stringy &stringy_, int n)
{
	for(int i=0;i<n;i++) cout << stringy_.str << endl;
	cout << endl;
}

void show(const char *str, int n)
{
	for(int i=0;i<n;i++) cout << str << endl;
	cout << endl;
}