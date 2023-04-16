#ifndef DATETIME_MINUTE_H
#define DATETIME_MINUTE_H

#include "TimeComponent.h"

class Minute : public TimeComponent
{
public:
        static constexpr uint64_t N_NANOSECONDS = 60'0000'000'000;

        explicit Minute(int minute) :
                TimeComponent(minute, N_NANOSECONDS) {}
};

#endif //DATETIME_MINUTE_H
