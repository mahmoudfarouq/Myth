#include "Room.h"
#include "Agent.h"
#include "FixedProp.h"
#include "Treasure.h"
#include "Prop.h"
#include "Player.h"

Room::Room()
{

}
Room::~Room()
{
    for(int i = 0; i < 4; i++) delete links[i];
}
Room::Room(QString name, QString discription, QString index, QGroupBox* con, Point point)
{
    dirs[0] = "WEST";
    dirs[1] = "NORTH";
    dirs[2] = "EAST";
    dirs[3] = "SOUTH";
    this->name = name;
    this->discription = discription;
    for(int i = 0; i < 4; i++) {links[i] = NULL; myMap[dirs[i]] = i;}
    container = con;
    container->setVisible(false);
    this->index = index;
    this->point = point;
}
QString Room::getName(){return name;}
QString Room::getDescription(){return discription;}
void Room::link(Room *r, QString direction, bool first)
{
    links[myMap[direction]] = new Link();
    links[myMap[direction]]->to     = r;
    links[myMap[direction]]->goDir  = direction;
    if(first){
        int index = (myMap[direction] > 1 ? myMap[direction]-2:myMap[direction]+2);
        r->link(this, dirs[index], false);
    }
}
Room* Room::getLinked(QString direction)
{
    return ( links[myMap[direction]] != NULL ? links[myMap[direction]]->to:NULL );
}
QString Room::printLinked()
{
    QString x = "";
    x += "The " + name + " is Connected to.. ";
    for(int i = 0; i < 4; i++){ x += (links[i] == NULL ? "":links[i]->to->name + " (" + dirs[i] + ")\n");}
    return x;
}
QString Room::PrintItems()
{
    QString x = "\nThe Items in this room are: \n";

    map<QString, Object*>::const_iterator it;
    for(it=InnerItems.begin(); it != InnerItems.end(); it++ )
    {
        x += ((it->second == NULL) ? "":it->first+"("+ it->second->getDescription() +")\n");
    }
    if(x.length() < 40) x = "\nThere are no Items over here!  \n";
    return x;
}

QString Room::printDetails(Agent *currentPlayer)
{
    QString x =
      getName() + "\n" + getDescription() + "\n"
    + printLinked()
    + PrintItems();
    return x;
}
bool Room::addItem(Object* item)
{
    if( InnerItems[item->getName()] != NULL ) return false;
    InnerItems[item->getName()] = item;
    return true;

}
bool Room::remItem(Object* item)
{
    if( InnerItems[item->getName()] == NULL ) return false;
    InnerItems[item->getName()] = NULL;
    return true;
}
