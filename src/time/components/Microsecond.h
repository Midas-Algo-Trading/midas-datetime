#ifndef DATETIME_MICROSECOND_H
#define DATETIME_MICROSECOND_H

#include "TimeComponent.h"

class Microsecond : public TimeComponent
{
public:
        explicit Microsecond(int microsecond) : TimeComponent(microsecond) {}
};

#endif //DATETIME_MICROSECOND_H
