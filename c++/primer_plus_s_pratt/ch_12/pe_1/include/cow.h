//
// Created by Dinir Imameev on 11/20/19.
// Github: @dinimar
//

#ifndef COW_LIB_COW_H
#define COW_LIB_COW_H

class Cow {
    char name[20];
    char * hobby;
    double weight;
public:
    Cow();
    Cow(const char * nm, const char * ho, double wt);
    Cow(const Cow &c);
    ~Cow();
    Cow & operator=(const Cow & c);
    void showCow() const; // display all cow data
};

#endif //COW_LIB_COW_H
