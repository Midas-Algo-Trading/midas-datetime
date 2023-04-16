#ifndef DATETIME_HOUR_H
#define DATETIME_HOUR_H

#include "TimeComponent.h"

class Hour : public TimeComponent
{
public:
        static constexpr uint64_t N_NANOSECONDS = 360'0000'000'000;

        explicit Hour(int hour) :
                TimeComponent(hour, N_NANOSECONDS) {}
};

#endif //DATETIME_HOUR_H
