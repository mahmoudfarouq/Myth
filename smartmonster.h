#ifndef SMARTMONSTER_H
#define SMARTMONSTER_H

#include "agent.h"

class SmartMonster : public Agent
{
public:
    SmartMonster();
    SmartMonster(QString n, QString d, Room* c, int h, int a, int de, QPixmap img);
    bool act(QString dir);
    bool Life(Agent *a);
    void setAll(Agent* player1, Agent *player2, map<QString, Room*> rooms);
    void AttackAll();
private:
    Agent* stPlayer;
    Agent* ndPlayer;
    map<QString, Room*> allRooms;
};

#endif // SMARTMONSTER_H
