#ifndef DATETIME_DAY_H
#define DATETIME_DAY_H

#include "../../Component.h"

/**
 * Represents an amount of days.
 *
 * Used in the 'Date' class to add to days to the date.
 */
struct Day : Component
{
        /**
         * Creates a 'Day' object which represents an amount of days.
         *
         * @param day the number of days to represent.
         */
        explicit Day(int day) : Component(day) {}
};

#endif //DATETIME_DAY_H
