#ifndef DATETIME_MICROSECOND_H
#define DATETIME_MICROSECOND_H

#include "../../Component.h"

class Microsecond : public Component
{
public:
        explicit Microsecond(int microsecond) : Component(microsecond) {}
};

#endif //DATETIME_MICROSECOND_H
