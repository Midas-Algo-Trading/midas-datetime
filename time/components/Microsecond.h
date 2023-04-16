#ifndef DATETIME_MICROSECOND_H
#define DATETIME_MICROSECOND_H

#include "TimeComponent.h"

class Microsecond : public TimeComponent
{
public:
        static constexpr uint64_t N_NANOSECONDS = 1'000;

        explicit Microsecond(int microsecond) :
                TimeComponent(microsecond, N_NANOSECONDS) {}
};

#endif //DATETIME_MICROSECOND_H
