#include "smartmonster.h"

SmartMonster::SmartMonster()
{

}
SmartMonster::SmartMonster(QString n, QString d, Room* c, int h, int a, int de, QPixmap img):Agent(img)
{
    health = h;
    attack = a;
    defense = de;
    name = n;
    CurrentPositon = c;
    discription = d;
    CurrentPositon->InnerChars[n] = this;
}
void SmartMonster::setAll(Agent* player1, Agent *player2, map<QString, Room*> rooms)
{
    stPlayer = player1;
    ndPlayer = player2;
    allRooms = rooms;
}
bool SmartMonster::act(QString dir)
{
    AttackAll();

    Point first = stPlayer->CurrentPositon->point;
    Point second= ndPlayer->CurrentPositon->point;
    Point monst = CurrentPositon->point;

    int firstFar = abs( first.x - monst.x  ) + abs(first.y - monst.y);
    int secondFar= abs( second.x- monst.x  ) + abs(second.y- monst.y);

    if(firstFar <= secondFar)
    {
        if( first.x == monst.x )
        {
            if( first.y < monst.y ){ monst.y--;}
            else if( first.y > monst.y ) {monst.y++;}
        }
        else if( first.y == monst.y )
        {
            if( first.x < monst.x ) { monst.x--;}
            else if( first.x > monst.x ) { monst.x++;}
        }
        else monst.x = first.x;
    }
    else
    {
        if( second.x == monst.x )
        {
            if( second.y < monst.y ) { monst.y--;}
            else if( second.y > monst.y ) {monst.y++;}
        }
        else if( second.y == monst.y )
        {
            if( second.x < monst.x ) { monst.x--;}
            else if( second.x > monst.x ) { monst.x++;}
        }
        else monst.x = second.x;

    }
    char x = (char)monst.x+48;
    QString pos = "";
    pos += x;
    x = (char)monst.y+48;
    pos += x;

    if(CurrentPositon->allLabels[name] != NULL)
        CurrentPositon->allLabels[name]->setPixmap( QPixmap() );
    CurrentPositon->InnerChars[getName()] = NULL;
    CurrentPositon = allRooms[ pos ];
    CurrentPositon->InnerChars[getName()] = this;
    if(CurrentPositon->allLabels[name] != NULL)
        CurrentPositon->allLabels[name]->setPixmap( image );

    AttackAll();
    return true;
}
void SmartMonster::AttackAll()
{
    map<QString, Agent*>::const_iterator it;
    for(it=CurrentPositon->InnerChars.begin(); it != CurrentPositon->InnerChars.end(); it++ )
    {
        if(it->second != NULL&&it->second->Life())
            if( it->second->getAttack() != attack && it->second->getAttack() != 1001  )
            {
                it->second->setHp( it->second->getHp() - attack + it->second->getDefense()/2 );
            }
    }
}

bool SmartMonster::Life (Agent *a)
{
    if (health <= 0 )
    {
        CurrentPositon->InnerChars[name] = NULL;
        return false ;
    }
    else {return true ;}
}
