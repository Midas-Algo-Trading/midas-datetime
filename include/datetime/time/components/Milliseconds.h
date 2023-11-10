#ifndef DATETIME_MILLISECONDS_H
#define DATETIME_MILLISECONDS_H

#include "../../../../src/time/TimeComponent.h"

/**
 * Number of milliseconds.
 *
 * Used in the 'Time' class to add to milliseconds to the 'Time'.
 */
struct Milliseconds : TimeComponent
{
    /**
     * Creates a 'Milliseconds' which represents an amount of milliseconds.
     *
     * @param millisecond number of milliseconds.
     */
    explicit Milliseconds(int64_t millisecond) :
        TimeComponent(millisecond) {}
};

#endif //DATETIME_MILLISECONDS_H
