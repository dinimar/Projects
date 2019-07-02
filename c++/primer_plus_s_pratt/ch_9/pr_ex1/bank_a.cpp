#include "bank_a.h"
#include <iostream>

BankA::BankA(const string &dep_name, 
		const string &a_num,
		double bal)
{
	this->dep_name = dep_name;
	this->a_num = a_num;
	this->bal = bal;
}

void BankA::show()
{
	using namespace std;

	cout << this->dep_name << " (" << this->a_num << ") Balance: " << this->bal << endl; 	
}

void BankA::deposit(double bal)
{
	this->bal += bal;
}

void BankA::withdraw(double bal)
{
	this->bal -= bal;
}