#ifndef DATETIME_DAY_H
#define DATETIME_DAY_H

#include "datetime/Component.h"

#include "DateComponent.h"

/**
 * Amount of days.
 *
 * Used in the 'Date' class to add to days to the 'Date'.
 */
struct Day : DateComponent
{
    /**
     * Creates a 'Day' which represents a number of days.
     *
     * @param day Number of days to represent.
     */
    explicit Day(int day) :
        DateComponent(day) {}
};

#endif //DATETIME_DAY_H
