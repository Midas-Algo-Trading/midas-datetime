#ifndef DATETIME_DAYS_H
#define DATETIME_DAYS_H

#include "../../../../src/Component.h"
#include "../../../../src/date/DateComponent.h"

/**
 * Amount of days.
 *
 * Used in the 'Date' class to add to days to the 'Date'.
 */
struct Days : DateComponent
{
    /**
     * Creates a 'Days' which represents a number of days.
     *
     * @param day Number of days to represent.
     */
    explicit Days(int64_t day) :
        DateComponent(day) {}
};

#endif //DATETIME_DAYS_H
