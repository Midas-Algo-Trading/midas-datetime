#ifndef DATETIME_MINUTE_H
#define DATETIME_MINUTE_H

#include "TimeComponent.h"

struct Minute : TimeComponent
{
        explicit Minute(int minute) : TimeComponent(minute) {}
};

#endif //DATETIME_MINUTE_H
