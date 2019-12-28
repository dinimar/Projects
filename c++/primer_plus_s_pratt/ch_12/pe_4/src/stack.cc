//
// Created by Dinir Imameev on 12/25/19.
// Github: @dinimar
//

#include "stack.h"

Stack::Stack(int n) {
    size = n;
    pitems = new Item[size];
    top = -1;
}

Stack::Stack(const Stack &st) {
    size = st.size;
    pitems = new Item[size];
    for(int i=0; i<size; i++) {
        pitems[i] = st.pitems[i];
    }
    //    std::copy(st.pitems, st.pitems+st.size, pitems);
    top = st.top;
}

Stack & Stack::operator=(const Stack &st) {
    if (this != &st) {
        delete [] pitems;
        size = st.size;
        pitems = new Item[size];
        for(int i=0; i<size; i++) {
           pitems[i] = st.pitems[i];
        }
//        pitems = std::copy(st.pitems, st.pitems+st.size, pitems);
        top = st.top;
    }

    return *this;
}

Stack::~Stack() {
    delete [] pitems;
}

bool Stack::isempty() const {
    return top == -1;
}

bool Stack::isfull() const {
    return top == size-1;
}

bool Stack::push(const Item &item) {
    if (top+1 < size) {
        pitems[++top] = item; // add value on the top; increase top idx

        return true;
    } else {
        return false;
    }
}

bool Stack::pop(Item & item) {
    if (top-1 >= -1) {
        item = pitems[top--]; // get top value; decrease top idx

        return true;
    } else {
        return false;
    }
}