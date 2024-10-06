#ifndef DATETIME_SECONDS_H
#define DATETIME_SECONDS_H

#include "../../../src/component.h"

/**
 * Number of seconds.
 *
 * Used in the 'Time' class to add to seconds to the 'Time'.
 */
struct Seconds : Component
{
    /**
     * Creates a 'Seconds' which represents an amount of seconds.
     *
     * @param second number of seconds.
     */
    explicit Seconds(int64_t second) :
        Component(second) {}
};

#endif //DATETIME_SECONDS_H
