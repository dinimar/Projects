//
// Created by Dinir Imameev on 12/25/19.
// Github: @dinimar
//

#include "stack.h"
#include <algorithm>

Stack::Stack(int n) {
    size = n;
    pitems = new Item[size];
    top = -1;
}

Stack::Stack(const Stack &st) {
    size = st.size;
    pitems = new Item[size];
    std::copy(st.pitems, st.pitems+st.size, pitems);
    top = st.top;
}

Stack & Stack::operator=(const Stack &st) {
    if (this != &st) {
        delete [] pitems;
        size = st.size;
        pitems = new Item[size];
        pitems = std::copy(st.pitems, st.pitems+st.size, pitems);
        top = st.top;
    }

    return *this;
}

Stack::~Stack() {
    delete [] pitems;
}

bool Stack::isempty() const {
    return top == -1 ? true : false;
}

bool Stack::isfull() const {
    return top == size-1 ? true : false;
}

bool Stack::push(const Item &item) {
    if (top != -1) {
        // shift array for 1 element to the right
        for (int i = top + 1; i > 0; i--) {
            pitems[i] = pitems[i - 1];
        }
    }
    pitems[0] = item; // add value in the beginning
    top++; // update top idx
}