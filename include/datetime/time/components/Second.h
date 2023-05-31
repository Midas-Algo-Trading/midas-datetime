#ifndef DATETIME_SECOND_H
#define DATETIME_SECOND_H

#include "datetime/time/components/TimeComponent.h"

/**
 * Number of seconds.
 *
 * Used in the 'Time' class to add to seconds to the 'Time'.
 */
struct Second : TimeComponent
{
    /**
     * Creates a 'Second' which represents an amount of seconds.
     *
     * @param second number of seconds.
     */
    explicit Second(int second) :
        TimeComponent(second) {}
};

#endif //DATETIME_SECOND_H
