#ifndef MONSTER_H
#define MONSTER_H
#include "Agent.h"

/*derived class from agent for Monsters*/
class Monster:public Agent
{
    public:
        //default constructor
        Monster();
        Monster(QString n, QString d, Room* c, int h, int a, int de, QPixmap img);
        bool act(QString dir);
        bool Life(Agent *a);
        void AttackAll();
    private:
};

#endif // MONSTER_H
