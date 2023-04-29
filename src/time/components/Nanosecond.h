#ifndef DATETIME_NANOSECOND_H
#define DATETIME_NANOSECOND_H

#include "TimeComponent.h"

struct Nanosecond : TimeComponent
{
        explicit Nanosecond(int nanosecond) : TimeComponent(nanosecond) {}
};

#endif //DATETIME_NANOSECOND_H
