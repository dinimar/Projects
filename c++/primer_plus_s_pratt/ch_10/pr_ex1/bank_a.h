#ifndef BANK_A
#define BANK_A 
#include <string>
using namespace std;

class BankA
{
private:
	string dep_name;
	string a_num;
	double bal;

public:
	BankA(const string &dep_name="Name", 
		const string &a_num="1234567890",
		double balance=0);

	void show();
	void deposit(double balance);
	void withdraw(double balance);

	// ~BankA();
};

#endif