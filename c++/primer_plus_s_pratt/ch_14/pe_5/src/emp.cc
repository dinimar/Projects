#include "emp.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::getline;

abstr_emp::~abstr_emp() {}

abstr_emp::abstr_emp()
{
    fname = "Lname";
    lname = "Fname";
    job = "job";
}

abstr_emp::abstr_emp(const std::string &fn, const std::string &ln,
                     const std::string &j)
{
    fname = fn;
    lname = ln;
    job = j;
}

void abstr_emp::ShowAll() const
{
    cout << "Name: " << fname << " " << lname << endl
         << "Job: " << job << endl;   
}

void abstr_emp::SetAll()
{
    cout << "Enter a first name: ";
    getline(cin, fname);

    cout << "Enter a last name: ";
    getline(cin, lname);

    cout << "Enter a job: ";
    getline(cin, job);
}

std::ostream & operator<<(std::ostream &os, const abstr_emp &e)
{
    os << e.fname << " " << e.lname << " " << e.job << endl;
}

manager::manager(const std::string &fn, const std::string &ln,
                 const std::string &j, int ico): abstr_emp(fn, ln, j)
{
    inchargeof = ico;
}

manager::manager(const abstr_emp &e, int ico): abstr_emp(e)
{
    inchargeof = ico;
}

void manager::ShowAll() const
{
    abstr_emp::ShowAll();
    cout << "In charge of: " << inchargeof << endl;
}

void manager::SetAll()
{    
    abstr_emp::SetAll();
    cout << "Enter in-charge-of number: ";

    std::string tmp;
    getline(cin, tmp);
    inchargeof = std::stoi(tmp);
}

fink::fink(const std::string &fn, const std::string &ln,
         const std::string &j, const std::string &rpo): abstr_emp(fn, ln, j)
{
    reportsto = rpo;
}

fink::fink(const abstr_emp &e, const std::string &rpo): abstr_emp(e)
{
    reportsto = rpo;
}

void fink::ShowAll() const
{
    abstr_emp::ShowAll();
    cout << "Reports to: " << reportsto << endl;
}

void fink::SetAll()
{
    abstr_emp::SetAll();
    cout << "Enter reports-to number: ";
    getline(cin, reportsto);
}

highfink::highfink(const std::string &fn, const std::string &ln,
                   const std::string &j, const std::string &rpo,
                   int ico): 
                   abstr_emp(fn, ln, j),  
                   fink(fn, ln, j, rpo), 
                   manager(fn, ln, j, ico)
{}

highfink::highfink(const abstr_emp &e, const std::string &rpo, int ico):
                   abstr_emp(e), fink(e, rpo), manager(e, ico)           
{}

highfink::highfink(const fink &f, int ico):
                   abstr_emp(f), fink(f), manager(f, ico)
{}

highfink::highfink(const manager &m, const std::string &rpo):
                   abstr_emp(m), manager(m), fink(m, rpo)
{}

void highfink::ShowAll() const
{
    abstr_emp::ShowAll();
    cout << "Reports to: " << ReportsTo() << endl;
    cout << "In-charge-of number: " << InChargeOf() << endl;
}

void highfink::SetAll()
{
    abstr_emp::SetAll();
    
    std::string buffer;    // buffer string for int value
    
    // Load reference vars for class attributes
    std::string & repTo = ReportsTo();
    int & ico = InChargeOf();

    // Promt attribute values
    cout << "Enter who reports to: ";
    getline(cin, repTo);
    cout << "Enter a in-charge-of number: ";
    getline(cin, buffer);
    ico = std::stoi(buffer);
}