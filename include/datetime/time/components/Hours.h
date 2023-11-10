#ifndef DATETIME_HOURS_H
#define DATETIME_HOURS_H

#include "../../../../src/time/TimeComponent.h"

/**
 * Number of hours.
 *
 * Used in the 'Time' class to add to hours to the 'Time'.
 */
struct Hours : TimeComponent
{
    /**
     * Creates a 'Hours' which represents an amount of hours.
     *
     * @param hour number of hours.
     */
    explicit Hours(int64_t hour) :
        TimeComponent(hour) {}
};

#endif //DATETIME_HOURS_H
