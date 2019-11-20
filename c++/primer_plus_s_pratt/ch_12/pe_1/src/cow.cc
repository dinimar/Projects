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

Cow::~Cow() {
    delete[] hobby;
}

void Cow::showCow() const {
    cout << "Name: " << name << endl;
    cout << "Hobby: " << hobby << endl;
    cout << "Weight: " << weight << endl;
}

