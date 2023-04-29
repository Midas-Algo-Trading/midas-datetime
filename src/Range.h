#ifndef DATETIME_RANGE_H
#define DATETIME_RANGE_H

#include "../util/exceptions/not_implemented_error.h"

template<typename T>
struct Range
{
        T start;
        T end;

        Range(T start, T end) :
                start(start),
                end(end)
        {
                if (start > end)
                        throw std::invalid_argument("Start must be less than or equal to end");
        }

        bool in_range(T t) const
        {
                return t >= start && t <= end;
        }
};

#endif //DATETIME_RANGE_H
