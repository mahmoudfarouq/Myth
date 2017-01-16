#ifndef PROP_H
#define PROP_H

#include "Object.h"

class Prop : public Object
{
    public:
        Prop();
        Prop(QString n, QString d, int atk, int def);
        bool active(Player *Holder);
        bool vanish(Player *Holder);
    protected:

    private:

};

#endif // PROP_H
