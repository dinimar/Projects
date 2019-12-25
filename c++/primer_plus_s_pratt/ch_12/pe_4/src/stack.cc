//
// Created by Dinir Imameev on 12/25/19.
// Github: @dinimar
//

#include "stack.h"
#include <algorithm>

Stack::Stack(int n) {
    int size = n;
    pitems = new Item[size];
    top = 0;
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
