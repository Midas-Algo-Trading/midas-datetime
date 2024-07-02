#ifndef TIMETIME_TIMERANGE_H
#define TIMETIME_TIMERANGE_H

#include "../../../src/Range.h"
#include "datetime/time/Time.h"

/**
 * Range of 'Times'.
 */
struct TimeRange : Range<Time>
{
    /**
     * Creates a 'TimeRange' with the range between 'start' and 'end'.
     *
     * @param start start of the range.
     * @param end end of the range.
     */
    TimeRange(const Time& start, const Time& end) :
        Range(start, end) {}
};

#endif //TIMETIME_TIMERANGE_H
