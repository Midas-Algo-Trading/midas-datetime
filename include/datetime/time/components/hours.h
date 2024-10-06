#ifndef DATETIME_HOURS_H
#define DATETIME_HOURS_H

#include "../../../src/component.h"

/**
 * Number of hours.
 *
 * Used in the 'Time' class to add to hours to the 'Time'.
 */
struct Hours : Component
{
    /**
     * Creates a 'Hours' which represents an amount of hours.
     *
     * @param hour number of hours.
     */
    explicit Hours(int64_t hour) :
        Component(hour) {}
};

#endif //DATETIME_HOURS_H
