#include <iostream>
#include "vintageport.h"

int main()
{
    Port p("Gallo", "tawny", 20);
    VintagePort vp("Gallo", 20, "Nick", 1900);
    vp.Show();

    return 0;
}