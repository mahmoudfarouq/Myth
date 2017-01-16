#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <QString>
#include <map>
#include <QGroupBox>
#include <QLabel>
#include <QDebug>
using namespace std;
class Agent;
class Object;
struct Point
{
    int x; int y;
    Point(){}
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};
class Room
{
    struct Link{Room* to; QString goDir;};
    public:
        //default constructor
        Room();
        ~Room();
        //default destructor
        //parametrized constructor, takes name of room, and discription
        Room(QString name, QString discription, QString index,  QGroupBox* con, Point point);
        //get name
        QString getName();
        //get discription
        QString getDescription();
        //returns the index of the "direction" in the arrayOfDirections
        void link(Room *r, QString direction, bool first = true);
        //returns the address of the room that connected to specific direction
        Room *getLinked(QString direction);
        //prints all connected rooms to this room {names and directions}
        QString printLinked();
        //prints allllll
        QString PrintItems();
        QString printDetails(Agent *currentPlayer);
        //for the inner characters
        map<QString, Agent*> InnerChars;
        map<QString, Object*> InnerItems;
        bool addItem(Object* item);
        bool remItem(Object* item);
        QGroupBox* container;
        void setAllLabels(map<QString, QLabel*> MM){ allLabels = MM; }
        map<QString, QLabel*> allLabels;
        Point point;
    private:
        //name of the room
        QString name;
        QString index;
        //discription of the room
        QString discription;
        //list of directions
        QString dirs[4] = {"WEST", "NORTH", "EAST", "SOUTH"};
        //the four links in an array
        Link *links[4];
        //map for dirs and thier index
        map<QString, int> myMap;



        /* not yet solved */
        //to know what Characters in the Room
        //Agent* arrayOfCharactersInRoom[5];

};

#endif // ROOM_H
