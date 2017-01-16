#include "player.h"

#include "Prop.h"
#include "FixedProp.h"
#include "Treasure.h"


Player::Player()
{

}
Player::Player(QString n, QString d, Room* c, int h, int a, int de, QPixmap img):Agent(img)
{
    health = h;
    attack = a;
    defense = de;
    name = n;
    CurrentPositon = c;
    discription = d;
    CurrentPositon->InnerChars[n] = this;

}

bool Player::act(QString dir)
{
    if(CurrentPositon->getLinked(dir) != NULL)
    {
        CurrentPositon->container->setEnabled(false);
        CurrentPositon->container->setVisible(false);

        if(CurrentPositon->allLabels[name] != NULL)
            CurrentPositon->allLabels[name]->setPixmap( QPixmap() );
        CurrentPositon->InnerChars[getName()] = NULL;
        CurrentPositon = CurrentPositon->getLinked(dir);
        CurrentPositon->InnerChars[getName()] = this;
        if(CurrentPositon->allLabels[name] != NULL)
            CurrentPositon->allLabels[name]->setPixmap( image );
        return true;
    }
    return false;
}
QString Player::sayIntro()
{
    return CurrentPositon->printDetails(this);
}
bool Player::Grab(QString item)
{
    if( CurrentPositon->InnerItems[item] != NULL )
    {
        CurrentPositon->InnerItems[item]->active(this);
        Items[item] = CurrentPositon->InnerItems[item];
        msg = item + " Grabbed";
        CurrentPositon->InnerItems[item] = NULL;
        return true;
    }
    return false;
}
bool Player::addItem(Object* item)
{
    if( Items[item->getName()] != NULL ) return false;
    Items[item->getName()] = item;
    counter++;
    return true;
}
bool Player::Fight(QString enemy)
{
    if( CurrentPositon->InnerChars[enemy] != NULL )
    {
        //hPower=1+rand()%(35-1+1);
        int fighterATK = attack;
        int enemyDEF = CurrentPositon->InnerChars[enemy]->getDefense();
        int enemyHP = CurrentPositon->InnerChars[enemy]->getHp();
        int mindamage = ((fighterATK+fighterATK/4)-(enemyDEF)-(enemyDEF/10)-(enemyDEF/100)-(enemyDEF/1000))/2;
        int maxdamage = ((fighterATK+fighterATK/2)-(enemyDEF)-(enemyDEF/10)-(enemyDEF/100)-(enemyDEF/1000))/2;
        int damage = rand()%(maxdamage-mindamage)+mindamage;
        if(fighterATK<enemyDEF) damage = rand()%2;
        CurrentPositon->InnerChars[enemy]->setHp(enemyHP-damage);
        if(CurrentPositon->InnerChars[enemy]->getHp()<=0){
                msg = "You attacked " + enemy + " and caused him "+ toString(damage) +" damage points, now he is Dead!.";
        }
        else
            msg = "You attacked " + enemy + " and caused him "+ toString(damage) + " damage points, now his HP is: " + toString(CurrentPositon->InnerChars[enemy]->getHp());
        return true;
    }
    msg = "Enemy Does not Exist Here. ";
    return false;
}
bool Player::Life()
{
    if (health <= 0 )
    {
        //CurrentPositon->InnerChars[name] = NULL;
        map<QString, Object*>::const_iterator it;
        for(it=Items.begin(); it != Items.end(); it++ )
        {
            CurrentPositon->InnerItems[it->first] = it->second;
        }
        return false ;
    }
    else {return true ;}
}
bool Player::hasWon()
{
    if( Items["Old Steel Key"] != NULL && CurrentPositon->InnerItems["The Pharaoh Treasue"] != NULL ) return true;
    return false;
}

bool Player::remItem(QString item)
{
    if( Items[item] == NULL )
    {
        msg ="this item does't exist here to remove it .. \n";
        return false;
    }
    else
    {
        Items[item]->vanish(this);
        Items[item] = NULL;
        msg = item + " Has been removed!. " ;
        counter--;
        return true;
    }

}

QString Player::PrintItems()
{
    QString x = "\nYou Have: \n";
    map<QString, Object*>::const_iterator it;
    for(it=Items.begin(); it != Items.end(); it++ )
    {
        x += ((it->second == NULL) ? "":it->first+"("+ it->second->getDescription() +")\n");
    }
    if(x.length() < 20) x = "\nYou Don't Have Any Items!\n";
    return x;
}
