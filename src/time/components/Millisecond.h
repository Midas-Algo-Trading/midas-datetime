#ifndef DATETIME_MILLISECOND_H
#define DATETIME_MILLISECOND_H

#include "TimeComponent.h"

struct Millisecond : TimeComponent
{
        explicit Millisecond(int millisecond) : TimeComponent(millisecond) {}
};

#endif //DATETIME_MILLISECOND_H
