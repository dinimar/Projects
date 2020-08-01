#include "cd.h"

class Classic: public Cd
{
private:
    char * primaryWork;
public:
    Classic();
    Classic(char * prW, char *s1, char *s2, int n, double x);
    ~Classic();

    void Report() const;

    Classic(const Classic &cl);
    Classic &operator=(const Classic &cl);
};

// Classic::Classic(/* args */)
// {
// }

// Classic::~Classic()
// {
// }
