#ifndef PLORG_H_
#define PLORG_H_ 
#include <string>
using namespace std;

class Plorg
{
private:
	string name;
	int ci;

public:
	Plorg(string name="Plorga", int ci=50);

	void setCi(int ci);
	void report() const;	
};

#endif