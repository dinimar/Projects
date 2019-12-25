//
// Created by Dinir Imameev on 12/25/19.
// Github: @dinimar
//


#include <stack.h>

int main(int argc, char **argv) {
    Stack st;
    Stack cp(11);

    st = st;
    st = cp;

    bool em = st.isempty();
    bool full = st.isfull();

    return 0;
}
