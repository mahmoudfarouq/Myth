#include "fixedprop.h"

FixedProp::FixedProp()
{

}
FixedProp::FixedProp(QString n, QString d, int hp):Object(n, d, hp, 0, 0)
{

}
bool FixedProp::active(Player *Holder)
{
    if(4000 - Holder->getHp() > HP)
    {
        Holder->setHp( Holder->getHp() + HP );
    }
    else
    {
        Holder->setHp(4000);
    }
    Holder->Items[Name] = NULL;
    return true;
}
