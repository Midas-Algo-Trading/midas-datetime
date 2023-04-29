#ifndef DATETIME_MINUTE_H
#define DATETIME_MINUTE_H

#include "TimeComponent.h"

class Minute : public TimeComponent
{
public:
        explicit Minute(int minute) : TimeComponent(minute) {}
};

#endif //DATETIME_MINUTE_H
