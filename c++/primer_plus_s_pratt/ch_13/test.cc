class Test
{
private:
    /* data */
    int k_;
public:
    Test(int k): k_(k){};
    ~Test();

    Test operator=(Test &);
};

Test::~Test()
{
}

Test Test::operator=(Test & test)
{
    if (this == &test)
        // return *this;

    k_ = test.k_;
    // return *this;
}

int main(int argc, char const *argv[])
{
    // Test t(8);
    // Test b(1);

    // b = b = b;

    int d = 0;
    const int & b = d;
    // b = 1;

    // b.operator=(b.operator=(b.operator=(b)));


    /* code */
    return 0;
}

