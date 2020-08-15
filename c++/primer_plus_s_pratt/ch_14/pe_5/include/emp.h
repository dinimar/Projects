#ifndef EMP_H_
#define EMP_H_

// emp.h -- header file for abstr_emp class and children
#include <iostream>
#include <string>

class abstr_emp
{
private:
    std::string fname; // abstr_emp's first name
    std::string lname; // abstr_emp's last name
    std::string job;

public:
    abstr_emp();
    abstr_emp(const std::string &fn, const std::string &ln,
              const std::string &j);
    virtual void ShowAll() const; // labels and shows all data
    virtual void SetAll();        // prompts user for values
    friend std::ostream & operator<<(std::ostream &os, const abstr_emp &e); // just displays first and last name
    virtual ~abstr_emp() = 0;                         // virtual base class
};

class employee : public abstr_emp
{
public:
    employee() = default;
    employee(const std::string &fn, const std::string & ln, const std::string &j): abstr_emp(fn, ln, j){};
    // virtual void ShowAll() const;
    // virtual void SetAll();
    ~employee() = default;
};

class manager : virtual public abstr_emp
{
private:
    int inchargeof; // number of abstr_emps managed
protected:
    int InChargeOf() const { return inchargeof; } // output
    int &InChargeOf() { return inchargeof; }      // input
public:
    manager() = default;
    manager(const std::string &fn, const std::string &ln,
            const std::string &j, int ico = 0);
    manager(const abstr_emp &e, int ico);
    manager(const manager &m) = default;
    virtual void ShowAll() const;
    virtual void SetAll();
    ~manager() = default;
};

class fink : virtual public abstr_emp
{
private:
    std::string reportsto; // to whom fink reports
protected:
    const std::string ReportsTo() const { return reportsto; }
    std::string &ReportsTo() { return reportsto; }
public:
    fink() = default;
    fink(const std::string &fn, const std::string &ln,
         const std::string &j, const std::string &rpo);
    fink(const abstr_emp &e, const std::string &rpo);
    fink(const fink &e) = default;
    virtual void ShowAll() const;
    virtual void SetAll();
    ~fink() = default;
};

class highfink : public manager, public fink // management fink
{
public:
    highfink() = default;
    highfink(const std::string &fn, const std::string &ln,
             const std::string &j, const std::string &rpo,
             int ico);
    highfink(const abstr_emp &e, const std::string &rpo, int ico);
    highfink(const fink &f, int ico);
    highfink(const manager &m, const std::string &rpo);
    highfink(const highfink &h) = default;
    virtual void ShowAll() const;
    virtual void SetAll();
    ~highfink() = default;
};

#endif