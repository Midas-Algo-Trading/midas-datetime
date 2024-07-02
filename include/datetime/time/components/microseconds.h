#ifndef DATETIME_MICROSECONDS_H
#define DATETIME_MICROSECONDS_H

#include "../../../src/Component.h"

/**
 * Number of microseconds.
 *
 * Used in the 'Time' class to add to microseconds to the 'Time'.
 */
struct Microseconds : Component
{
    /**
     * Creates a 'Microseconds' which represents an amount of microseconds.
     *
     * @param microsecond number of microseconds.
     */
    explicit Microseconds(int64_t microsecond) :
        Component(microsecond) {}
};

#endif //DATETIME_MICROSECONDS_H
