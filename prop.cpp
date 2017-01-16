#include "prop.h"

Prop::Prop()
{

}


Prop::Prop(QString n, QString d, int atk, int def):Object(n, d, 0, atk, def)
{

}
bool Prop::active(Player *Holder)
{
    Holder->setAttributes(HP,ATK, DEF );
    return true;
}
bool Prop::vanish(Player *Holder)
{
    Holder->setAttributes( -HP, -ATK, -DEF );
    return true;
}
