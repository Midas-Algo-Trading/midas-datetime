#ifndef DATETIME_NANOSECOND_H
#define DATETIME_NANOSECOND_H

#include "datetime/time/components/TimeComponent.h"

/**
 * Number of nanoseconds.
 *
 * Used in the 'Time' class to add to nanoseconds to the 'Time'.
 */
struct Nanosecond : TimeComponent
{
    /**
     * Creates a 'Nanosecond' which represents an amount of nanoseconds.
     *
     * @param nanosecond number of nanoseconds.
     */
    explicit Nanosecond(int64_t nanosecond) :
        TimeComponent(nanosecond) {}
};

#endif //DATETIME_NANOSECOND_H
