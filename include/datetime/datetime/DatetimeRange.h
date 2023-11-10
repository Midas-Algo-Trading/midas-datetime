#ifndef DATETIME_DATETIMERANGE_H
#define DATETIME_DATETIMERANGE_H

#include <utility>
#include "Datetime.h"
#include "../../../src/Range.h"

/**
 * 'Range' of 'Datetimes'.
 */
struct DatetimeRange : Range<Datetime>
{
    /**
     * Creates a 'DatetimeRange' with the range being from 'start' to 'end'.
     *
     * @param start start of the range.
     * @param end end of the range.
     */
    DatetimeRange(const Datetime& start, const Datetime& end) :
        Range(start, end) {}
};

#endif //DATETIME_DATETIMERANGE_H
