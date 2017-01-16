#ifndef AGENT_H
#define AGENT_H
#include <iostream>
#include <map>
#include <QPixmap>
#include "Room.h"
/*base class for Player and Monsters*/
class Agent
{
public:
    Agent();
    Agent(QPixmap img);
    ~Agent();
    virtual bool act(QString dir)=0;   //pure virtual function, must be overloaded in the derived classes
    virtual QString sayIntro(){return "";}
    virtual bool Grab(QString item){return false;}
    virtual bool Fight(QString enemy){return false;}
    virtual QString getMessage(){return "";}
    virtual void setHp(int hp){health = hp;}
    int getHp(){return health;}

    virtual bool addItem(Object* item){return false;}
    virtual bool remItem(Object* item){return false;}
    virtual int getAttack(){return attack;}
    virtual int getDefense() {return defense;}
    QString toString(int x);
    virtual bool hasWon(){}

    virtual bool Life ();
    Room* CurrentPositon;               //every agent must has his address(CurrentROOM)
    QString name;
    QString discription;
    QString getDiscription()
    {
        QString x ="" ;
        x+= discription +")" +"\tHp: "+ ( toString(health) == "" ? "(Dead)":toString(health) ) + "  " + "ATK: " +toString(attack) +"  " + "DEF: " +toString(defense)+ " \n";
        return x ;
    }
    void setName(QString s){name = s;}
    QString getName(){return name;}
    QPixmap image;
protected:                  //protected so the derived classes can access the variables
    int health;             //NOT designed yet but sounds obvious
    int attack;              //NOT designed yet but sounds obvious
    int defense;
};

#endif // AGENT_H
