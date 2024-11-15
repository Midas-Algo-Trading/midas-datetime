#ifndef DATETIME_DATERANGE_H
#define DATETIME_DATERANGE_H

#include "datetime/date/date.h"
#include <../../../src/range.h>

/**
 * Range of 'Dates'.
 */
struct DateRange : Range<Date>
{
    /**
     * Creates a 'DateRange' with the range between 'start' and 'end'.
     *
     * @param start start of the range.
     * @param end end of the range.
     */
    DateRange(const Date& start, const Date& end) :
        Range(start, end) {}
};

#endif //DATETIME_DATERANGE_H
