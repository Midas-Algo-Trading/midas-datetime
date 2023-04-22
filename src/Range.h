#ifndef DATETIME_RANGE_H
#define DATETIME_RANGE_H

#include "../util/exceptions/NotImplementedError.h"

template<typename T>
struct Range
{
        T start;
        T end;

        Range(T start, T end) :
                start(start),
                end(end) {}

        bool in_range(T t) const
        {
                return t >= start && t <= end;
        }
};

#endif //DATETIME_RANGE_H
