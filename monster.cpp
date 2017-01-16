#include "monster.h"

Monster::Monster()
{

}
Monster::Monster(QString n, QString d, Room* c, int h, int a, int de, QPixmap img):Agent(img)
{
    health = h;
    attack = a;
    defense = de;
    name = n;
    CurrentPositon = c;
    discription = d;
    CurrentPositon->InnerChars[n] = this;
}
bool Monster::act(QString dir)
{
    AttackAll();
    if(CurrentPositon->getLinked(dir) != NULL)
    {        
        if(CurrentPositon->allLabels[name] != NULL)
            CurrentPositon->allLabels[name]->setPixmap( QPixmap() );

        CurrentPositon->InnerChars[getName()] = NULL;
        CurrentPositon = CurrentPositon->getLinked(dir);
        CurrentPositon->InnerChars[getName()] = this;

        if(CurrentPositon->allLabels[name] != NULL)
            CurrentPositon->allLabels[name]->setPixmap( image );
        return true;
    }
    AttackAll();
}
void Monster::AttackAll()
{
    map<QString, Agent*>::const_iterator it;
    for(it=CurrentPositon->InnerChars.begin(); it != CurrentPositon->InnerChars.end(); it++ )
    {
        if(it->second != NULL&&it->second->Life())
            if( it->second->getAttack() != attack && it->second->getAttack() != 2001 )
            {
                it->second->setHp( it->second->getHp() - attack + it->second->getDefense()/2 );
            }
    }
}

bool Monster::Life (Agent *a)
{
    if (health <= 0 )
    {
        CurrentPositon->InnerChars[name] = NULL;
        return false ;
    }
    else {return true ;}
}

