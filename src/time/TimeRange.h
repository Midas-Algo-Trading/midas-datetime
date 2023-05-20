#ifndef DATETIME_TIMERANGE_H
#define DATETIME_TIMERANGE_H

#include "Time.h"
#include "../Range.h"

struct TimeRange : public Range<Time>
{
        TimeRange(Time start, Time end) :
                Range(std::move(start), std::move(end)) {}
};

#endif //DATETIME_TIMERANGE_H
