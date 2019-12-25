//
// Created by Dinir Imameev on 12/25/19.
// Github: @dinimar
//


#include <stack.h>

int main(int argc, char **argv) {
    int size = 11;

    Stack st;
    Stack cp(size);

    st = st;
    st = cp;

    for (int i = 0; i < size; ++i) {
        st.push(Item(10-i));
    }

    bool em = st.isempty();
    bool full = st.isfull();

    return 0;
}
