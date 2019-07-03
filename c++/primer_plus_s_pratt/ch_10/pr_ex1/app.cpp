#include "bank_a.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
	using namespace std;

	BankA bank_a(string("Rockfeller"), string("5051"), 1000);
	bank_a.show();

	cout << "\nDepositing 10 units:\n";
	bank_a.deposit(10);
	bank_a.show();

	cout << "\nWithdrawig 1000 units:\n";
	bank_a.withdraw(1000);
	bank_a.show();

	return 0;
}