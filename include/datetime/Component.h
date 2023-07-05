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
    uint32_t value;

    /**
     * Creates a 'Component' whose 'value' matches 'value'.
     *
     * @param value value to have the newly created 'Component' set to.
     */
    explicit Component(uint64_t value) :
        value(value) {}
};

#endif //DATETIME_COMPONENT_H
