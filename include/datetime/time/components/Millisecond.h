#ifndef DATETIME_MILLISECOND_H
#define DATETIME_MILLISECOND_H

#include "datetime/time/components/TimeComponent.h"

/**
 * Number of milliseconds.
 *
 * Used in the 'Time' class to add to milliseconds to the 'Time'.
 */
struct Millisecond : TimeComponent
{
    /**
     * Creates a 'Millisecond' which represents an amount of milliseconds.
     *
     * @param millisecond number of milliseconds.
     */
    explicit Millisecond(uint32_t millisecond) :
        TimeComponent(millisecond) {}
};

#endif //DATETIME_MILLISECOND_H
