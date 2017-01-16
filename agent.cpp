#include "agent.h"

Agent::Agent(QPixmap img)
{
    image = img;
}
Agent::Agent()
{

}
Agent::~Agent()
{
    delete CurrentPositon;
}
bool Agent::Life ()
{
    if (health <= 0 ) return false ;
    else {return true ;}
}

QString Agent::toString(int x)
{
    int len=0;
    int x_ = x;
    while(x_ > 0){x_ /= 10;len++;}
    char *array = new char[len];
    int i = 0;
    while(x > 0)
    {
        int z = (x%10);
        char c = (char)(z+48);
        if(z >= 10){c = (char) z+55;}
        array[len-i-1] = c;
        x /= 10;
        i++;
    }
    array[len] = '\0';
    return array;
}
