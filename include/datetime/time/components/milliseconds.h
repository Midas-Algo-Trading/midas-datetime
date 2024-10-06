#ifndef DATETIME_MILLISECONDS_H
#define DATETIME_MILLISECONDS_H

#include "../../../src/component.h"

/**
 * Number of milliseconds.
 *
 * Used in the 'Time' class to add to milliseconds to the 'Time'.
 */
struct Milliseconds : Component
{
    /**
     * Creates a 'Milliseconds' which represents an amount of milliseconds.
     *
     * @param millisecond number of milliseconds.
     */
    explicit Milliseconds(int64_t millisecond) :
        Component(millisecond) {}
};

#endif //DATETIME_MILLISECONDS_H
