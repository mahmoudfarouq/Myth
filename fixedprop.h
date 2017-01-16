#ifndef FIXEDPROB_H
#define FIXEDPROB_H

#include "Object.h"

class FixedProp : public Object
{
    public:
        FixedProp();
        FixedProp(QString n, QString d, int hp);
        bool active(Player *Holder);
    protected:

    private:
};

#endif // FIXEDPROB_H
