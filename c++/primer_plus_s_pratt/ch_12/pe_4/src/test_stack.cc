//
// Created by Dinir Imameev on 12/25/19.
// Github: @dinimar
//


#include <iostream>
#include "stack.h"

using namespace std;

int main(int argc, char **argv) {
    int size = 11;

    Stack st;
    Stack cp(size);

    st = st;
    st = cp;

    if (st.isempty()) cout << "Stack is empty" << endl;
    // Test push function
    for (int i = 0; i < size; ++i) {
        if (st.push(Item(10-i))) cout << "Item("<<i<<")'s successfully added" << endl;
    }
    if (st.isfull()) cout << "Stack is full" << endl;


    return 0;
}
