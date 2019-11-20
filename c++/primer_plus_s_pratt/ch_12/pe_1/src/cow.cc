//
// Created by Dinir Imameev on 11/20/19.
// Github: @dinimar
//

#include "cow.h"
#include <cstring>
#include <iostream>

using namespace std;

Cow::Cow() {
    // init name
    char name_[]= "Cow";
    strcpy(name, name_);
    // init hobby
    char *hobby_ = "hobby";
    hobby = new char[strlen(hobby_)+1];
    strcpy(hobby, hobby_);
    // init weight
    weight = 100;
}

Cow::Cow(const char * nm, const char * ho, double wt) {
    // set name value
    strcpy(name, nm);
    // set hobby value
    hobby = new char[strlen(ho)+1];
    strcpy(hobby, ho);
    // set weight value
    weight = wt;
}

Cow::~Cow() {
    delete[] hobby;
}

void Cow::showCow() const {
    cout << "Name: " << name << endl;
    cout << "Hobby: " << hobby << endl;
    cout << "Weight: " << weight << endl << endl;
}

