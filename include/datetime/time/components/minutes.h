#ifndef DATETIME_MINUTES_H
#define DATETIME_MINUTES_H

#include "../../../src/component.h"

/**
 * Number of minutes.
 *
 * Used in the 'Time' class to add to minutes to the 'Time'.
 */
struct Minutes : Component
{
    /**
     * Creates a 'Minutes' which represents an amount of minutes.
     *
     * @param minute number of minutes.
     */
    explicit Minutes(int64_t minute) :
        Component(minute) {}
};

#endif //DATETIME_MINUTES_H
