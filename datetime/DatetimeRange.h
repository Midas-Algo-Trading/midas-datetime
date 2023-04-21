#ifndef DATETIME_DATETIMERANGE_H
#define DATETIME_DATETIMERANGE_H

#include <utility>

#include "Datetime.h"
#include "../Range.h"

class DatetimeRange : public Range<Datetime>
{
public:
        DatetimeRange(const Datetime start, const Datetime end) :
                Range(std::move(start), std::move(end)) {}
};

#endif //DATETIME_DATETIMERANGE_H
