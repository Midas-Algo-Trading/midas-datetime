#ifndef DATETIME_COMPONENT_H
#define DATETIME_COMPONENT_H

/**
 * Component of 'Date' or 'Time'.
 */
struct Component
{
    /**
     * Value of this 'Component'.
     */
    int value;

    /**
     * Creates a 'Component' whose 'value' matches 'value'.
     *
     * @param value value to have the newly created 'Component' set to.
     */
    explicit Component(int value) :
        value(value) {}
};

#endif //DATETIME_COMPONENT_H
