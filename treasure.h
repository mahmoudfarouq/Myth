#ifndef TREASURE_H
#define TREASURE_H

#include "Object.h"
#include "FixedProp.h"
#include <map>

class Treasure : public Object
{
    public:
        Treasure();
        Treasure(QString n, QString d);
        bool active(Player *Holder);
        bool vanish(Player *Holder);
    protected:

    private:

};

#endif // TREASURE_H
