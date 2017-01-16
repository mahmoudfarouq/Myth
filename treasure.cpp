#include "treasure.h"

Treasure::Treasure()
{

}

Treasure::Treasure(QString n, QString d):Object(n, d, 0, 0, 0)
{

}
bool Treasure::active(Player *Holder)
{
    map<QString, Object*> Items = Holder->getItems();
    map<QString, Object*>::const_iterator it;
    for(it = Items.begin(); it != Items.end(); it++)
    {
        if(it->second->getName() == "trueKey")
        {
            return true;
        }
    }
    return false;
}
bool Treasure::vanish(Player *Holder)
{
    return true;
}
