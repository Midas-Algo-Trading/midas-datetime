#ifndef DATETIME_MICROSECOND_H
#define DATETIME_MICROSECOND_H

#include "TimeComponent.h"

struct Microsecond : TimeComponent
{
        explicit Microsecond(int microsecond) : TimeComponent(microsecond) {}
};

#endif //DATETIME_MICROSECOND_H
