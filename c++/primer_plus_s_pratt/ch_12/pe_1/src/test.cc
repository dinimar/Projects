//
// Created by Dinir Imameev on 11/20/19.
// Github: @dinimar
//

#include "cow.h"

int main(int argc, char** argv) {
    Cow cow1;
    cow1.showCow();

    Cow cow2{"Cow2", "hobby2", 100};
    cow2.showCow();

    Cow cow3{"Test more than nineteen symbols initalization.", "hobby2", 100};
    cow3.showCow();
    return 0;
}