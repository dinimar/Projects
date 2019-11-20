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
    if (strlen(nm) > 19) {
        for(int i=0; i<19; i++) name[i] = *(nm+i);
        name[19] = '\0';
    } else {
        strcpy(name, nm);
    }
    // set hobby value
    hobby = new char[strlen(ho)+1];
    strcpy(hobby, ho);
    // set weight value
    weight = wt;
}

Cow::Cow(const Cow &c) {
    // set name value
    if (strlen(c.name) > 19) {
        for(int i=0; i<19; i++) name[i] = *(c.name+i);
        name[19] = '\0';
    } else {
        strcpy(name, c.name);
    }
    // set hobby value
    delete[] hobby;
    hobby = new char[strlen(c.hobby)+1];
    strcpy(hobby, c.hobby);
    // set weight value
    weight = c.weight;
}

Cow::~Cow() {
    delete[] hobby;
}

void Cow::showCow() const {
    cout << "Name: " << name << endl;
    cout << "Hobby: " << hobby << endl;
    cout << "Weight: " << weight << endl << endl;
}

