#ifndef DATETIME_COMPONENT_H
#define DATETIME_COMPONENT_H

#include <cstdint>

/**
 * Component of 'Date' or 'Time'.
 */
struct Component
{
    /**
     * Value of this 'Component'.
     */
    int64_t value;

    /**
     * Creates a 'Component' whose 'value' matches 'value'.
     *
     * @param value value to have the newly created 'Component' set to.
     */
    explicit Component(int64_t value) :
        value(value) {}
};

#endif //DATETIME_COMPONENT_H
