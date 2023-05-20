#ifndef DATETIME_DATERANGE_H
#define DATETIME_DATERANGE_H

#include "Date.h"
#include "../Range.h"

struct DateRange : public Range<Date>
{
        DateRange(Date start, Date end) :
                Range(start, end) {}
};

#endif //DATETIME_DATERANGE_H
