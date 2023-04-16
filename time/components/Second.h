#ifndef DATETIME_SECOND_H
#define DATETIME_SECOND_H

#include "TimeComponent.h"

class Second : public TimeComponent
{
public:
        static constexpr uint64_t N_NANOSECONDS = 1'000'000'000;

        explicit Second(int second) :
                TimeComponent(second, N_NANOSECONDS) {}
};

#endif //DATETIME_SECOND_H
