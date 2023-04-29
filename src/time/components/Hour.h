#ifndef DATETIME_HOUR_H
#define DATETIME_HOUR_H

#include "TimeComponent.h"

struct Hour : TimeComponent
{
        explicit Hour(int hour) : TimeComponent(hour) {}
};

#endif //DATETIME_HOUR_H
