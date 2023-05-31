#ifndef DATETIME_HOUR_H
#define DATETIME_HOUR_H

#include "datetime/time/components/TimeComponent.h"

/**
 * Number of hours.
 *
 * Used in the 'Time' class to add to hours to the 'Time'.
 */
struct Hour : TimeComponent
{
    /**
     * Creates a 'Hour' which represents an amount of hours.
     *
     * @param hour number of hours.
     */
    explicit Hour(int hour) :
        TimeComponent(hour) {}
};

#endif //DATETIME_HOUR_H
