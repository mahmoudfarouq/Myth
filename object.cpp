#include "object.h"

Object::Object()
{

}
Object::Object(QString n, QString d, int hp, int atk, int def)
{
    Name = n;
    Description = d;
    HP = hp;
    ATK = atk;
    DEF = def;
}
