// usedma.cpp -- inheritance, friends, and DMA
// compile with dma.cpp
#include <iostream>
#include "dma.h"

int main()
{
    using std::cout;
    using std::endl;

    ABC * abcList[3];

    abcList[0] = new baseDMA("Portabelly", 8);
    abcList[1] = new lacksDMA("red", "Blimpo", 4);
    abcList[2] = new hasDMA("Mercator", "Buffalo Keys", 5);

    for(auto & abc: abcList)
    {
        abc->View();
        std::cout << std::endl;
    }
    
    return 0;
}