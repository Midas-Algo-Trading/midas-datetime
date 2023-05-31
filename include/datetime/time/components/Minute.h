#ifndef DATETIME_MINUTE_H
#define DATETIME_MINUTE_H

#include "datetime/time/components/TimeComponent.h"

/**
 * Number of minutes.
 *
 * Used in the 'Time' class to add to minutes to the 'Time'.
 */
struct Minute : TimeComponent
{
    /**
     * Creates a 'Minute' which represents an amount of minutes.
     *
     * @param minute number of minutes.
     */
    explicit Minute(int minute) :
        TimeComponent(minute) {}
};

#endif //DATETIME_MINUTE_H
