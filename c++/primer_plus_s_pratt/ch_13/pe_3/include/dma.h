// dma.h -- inheritance and dynamic memory allocation
#ifndef DMA_H_
#define DMA_H_
#include <iostream>

class ABC
{
private:
    char * label;
    int rating;
public:
    ABC(const char *l = "null", int r = 0);
    virtual ~ABC();

    ABC(const ABC &rs);
    ABC &operator=(const ABC &rs);

    friend std::ostream &operator<<(std::ostream &os,
                                    const ABC &rs);
    virtual void View();
};

// Base Class Using DMA
class baseDMA : public ABC
{
public:
    baseDMA(const char *l, int r);
    // ~baseDMA();
    
    friend std::ostream &operator<<(std::ostream &os,
                                    const baseDMA &rs);
};

// derived class without DMA
// no destructor needed
// uses implicit copy constructor
// uses implicit assignment operator
class lacksDMA : public ABC
{
private:
    enum
    {
        COL_LEN = 40
    };
    char color[COL_LEN];

public:
    lacksDMA(const char *c = "blank", const char *l = "null",
             int r = 0);
    lacksDMA(const char *c, const ABC &rs);

    void View();
    
    friend std::ostream &operator<<(std::ostream &os,
                                    const lacksDMA &rs);
};
// derived class with DMA
class hasDMA : public ABC
{
private:
    char *style;

public:
    hasDMA(const char *s = "none", const char *l = "null",
           int r = 0);
    hasDMA(const char *s, const ABC &rs);
    ~hasDMA();

    hasDMA(const hasDMA &hs);
    hasDMA &operator=(const hasDMA &rs);

    void View();
    
    friend std::ostream &operator<<(std::ostream &os,
                                    const hasDMA &rs);
};
#endif