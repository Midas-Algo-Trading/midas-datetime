#ifndef DATETIME_HOUR_H
#define DATETIME_HOUR_H

#include "TimeComponent.h"

class Hour : public TimeComponent
{
public:
        explicit Hour(int hour) : TimeComponent(hour) {}
};

#endif //DATETIME_HOUR_H
