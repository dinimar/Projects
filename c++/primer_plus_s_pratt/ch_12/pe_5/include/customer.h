#ifndef CUSTOMER_H_
#define CUSTOMER_H_

// This queue will contain Customer items
class Customer
{
private:
    long arrive_; // arrival time for customer
    int processtime_; // processing time for customer
public:
    Customer();
    void set(long when);
    long when() const;
    int ptime() const;
};

#endif