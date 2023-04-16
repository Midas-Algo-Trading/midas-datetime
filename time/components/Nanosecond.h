#ifndef DATETIME_NANOSECOND_H
#define DATETIME_NANOSECOND_H

#include "TimeComponent.h"

class Nanosecond : public TimeComponent
{
public:
        static constexpr uint64_t N_NANOSECONDS = 1;

        explicit Nanosecond(int nanosecond) :
                TimeComponent(nanosecond, N_NANOSECONDS) {}
};

#endif //DATETIME_NANOSECOND_H
