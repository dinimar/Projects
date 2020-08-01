#ifndef V_PORT_H
#define V_PORT_H
#include "port.h"
class VintagePort : public Port // style necessarily = "vintage"
{
private:
    char *nickname; // i.e., "The Noble" or "Old Velvet", etc.
    int year;       // vintage year
public:
    VintagePort();
    VintagePort(const char *br, int b, const char *nn, int y);
    ~VintagePort() { delete[] nickname; }

    VintagePort(const VintagePort &vp);
    VintagePort &operator=(const VintagePort &vp);
    
    void Show() const;
    friend ostream &operator<<(ostream &os, const VintagePort &vp);
};
#endif