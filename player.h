#ifndef PLAYER_H
#define PLAYER_H
#include "agent.h"

class Object;

/*derived class from agent for Players*/
class Player:public Agent
{
    public:
        //default constructor
        Player();
        Player(QString n, QString d, Room* c, int h, int a, int de, QPixmap img);
        bool act(QString dir);
        QString sayIntro();
        void setAttributes(int h, int atk, int def){ health += h;attack += atk; defense += def; }
        void setHp(int hp){health = hp;}
        int getHp(){return health;}
        void setDefense(int de){defense=de;}
        bool Grab(QString item);
        bool Fight(QString enemy);
        QString getMessage(){return msg;}
        bool hasWon();

        bool Life ();
        bool addItem(Object* item);
        bool remItem(QString item);
        bool dropItem(Object* item);
        QString PrintItems();

        map<QString, Object*> Items;
        map<QString, Object*> getItems(){return Items;}
    private:
        QString msg;
        int counter =0;

};

#endif // PLAYER_H
