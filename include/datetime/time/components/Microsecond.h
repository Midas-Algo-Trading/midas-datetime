#ifndef DATETIME_MICROSECOND_H
#define DATETIME_MICROSECOND_H

#include "datetime/time/components/TimeComponent.h"

/**
 * Number of microseconds.
 *
 * Used in the 'Time' class to add to microseconds to the 'Time'.
 */
struct Microsecond : TimeComponent
{
    /**
     * Creates a 'Microsecond' which represents an amount of microseconds.
     *
     * @param microsecond number of microseconds.
     */
    explicit Microsecond(int64_t microsecond) :
        TimeComponent(microsecond) {}
};

#endif //DATETIME_MICROSECOND_H
