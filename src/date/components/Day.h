#ifndef DATETIME_DAY_H
#define DATETIME_DAY_H

#include "../../Component.h"

struct Day : Component
{
        explicit Day(int day) : Component(day) {}
};

#endif //DATETIME_DAY_H
