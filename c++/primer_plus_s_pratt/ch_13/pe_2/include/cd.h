#ifndef CD_H_
#define CD_H_
class Cd
{ // represents a CD disk
private:
    char * performers;
    char * label;
    int selections;  // number of selections
    double playtime; // playing time in minutes

    // safely copies string
    // if copies only part of src that is
    // not larger by length than dest length
    void CopyString(char *dest, char *src);

    // makes work strlen for char arrays
    // whether they passed by pointer or access directly
    void InitCharArrays();

public:
    Cd(char *s1, char *s2, int n, double x);
    Cd();
    virtual ~Cd() = default;
    virtual void Report() const; // reports all CD data
    
    Cd(const Cd &d);
    Cd &operator=(const Cd &d);
};

#endif