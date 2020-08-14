#include "pokerplayer.h"

void PokerPlayer::Set()
{
    Person::Get();
}

int PokerPlayer::Draw()
{
    return mUniformDist(mEngine);
}

void PokerPlayer::Show()
{
    Person::Show();   
}