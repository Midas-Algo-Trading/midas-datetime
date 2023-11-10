#ifndef DATETIME_NANOSECONDS_H
#define DATETIME_NANOSECONDS_H

#include "../../../../src/time/TimeComponent.h"

/**
 * Number of nanoseconds.
 *
 * Used in the 'Time' class to add to nanoseconds to the 'Time'.
 */
struct Nanoseconds : TimeComponent
{
    /**
     * Creates a 'Nanoseconds' which represents an amount of nanoseconds.
     *
     * @param nanosecond number of nanoseconds.
     */
    explicit Nanoseconds(int64_t nanosecond) :
        TimeComponent(nanosecond) {}
};

#endif //DATETIME_NANOSECONDS_H
