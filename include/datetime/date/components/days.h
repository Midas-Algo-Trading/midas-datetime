#ifndef DATETIME_DAYS_H
#define DATETIME_DAYS_H

#include "../../../../src/component.h"

/**
 * Amount of days.
 *
 * Used in the 'Date' class to add to days to the 'Date'.
 */
struct Days : Component
{
    /**
     * Creates a 'Days' which represents a number of days.
     *
     * @param day Number of days to represent.
     */
    explicit Days(int64_t day) :
        Component(day) {}
};

#endif //DATETIME_DAYS_H
