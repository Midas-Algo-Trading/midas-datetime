#ifndef DATETIME_NANOSECOND_H
#define DATETIME_NANOSECOND_H

#include "../../Component.h"

class Nanosecond : public Component
{
public:
        explicit Nanosecond(int nanosecond) : Component(nanosecond) {}
};

#endif //DATETIME_NANOSECOND_H
