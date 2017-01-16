#ifndef OBJECT_H
#define OBJECT_H
#include "Player.h"

class Object
{
    public:
        Object();
        Object(QString n, QString d, int hp, int atk, int def);

        QString getName(){return Name;}
        QString getDescription(){return Description;}
        virtual bool active(Player *Holder) = 0;
        virtual bool vanish(Player *Holder){return true;}
    protected:
        QString Name;
        QString Description;
        int HP;         //hp: HEALTH POINTS
        int ATK;        //ATK: attack
        int DEF;        //DEF: defense
    private:
};

#endif // OBJECT_H
