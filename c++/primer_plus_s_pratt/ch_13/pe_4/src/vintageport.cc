#include "vintageport.h"
#include <cstring>

VintagePort::VintagePort()
{
    nickname = new char[5];
    std::strcpy(nickname, "Nick");

    year = 0;
}

VintagePort::VintagePort(const char *br, int b, const char *nn, int y): Port(br, "none", b), year(y)
{
    nickname = new char[std::strlen(nn)+1];
    std::strcpy(nickname, nn);
}

VintagePort::VintagePort(const VintagePort & vp): Port(vp), year(vp.year)
{
    delete[] nickname;
    nickname = new char[std::strlen(vp.nickname)+1];
    std::strcpy(nickname, vp.nickname);
}

VintagePort & VintagePort::operator=(const VintagePort & vp)
{
    if (this != &vp)
    {
        delete[] nickname;
        nickname = new char[std::strlen(vp.nickname)+1];
        std::strcpy(nickname, vp.nickname);

        year = vp.year;
    }

    return *this;
}

void VintagePort::Show() const
{
    Port::Show();
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Year: " << year << std::endl;
}
