#include "baddude.h"

void BadDude::Set()
{
    Person::Get();
}

void BadDude::Show()
{
    Gunslinger::Show();
}

double BadDude::GDraw()
{
    return Gunslinger::Draw();
}

int BadDude::CDraw()
{
    return PokerPlayer::Draw();
}