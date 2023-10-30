#ifndef INCLUDE_DATETIME_DATECOMPONENT_H
#define INCLUDE_DATETIME_DATECOMPONENT_H

#include "datetime/Component.h"

/**
 * Component for 'Date'.
 */
struct DateComponent : Component
{
    /**
     * Creates a 'DateComponent' whose 'value' matches 'value'.
     *
     * @param value the value to have the newly created 'DateComponent' set to.
     */
    explicit DateComponent(int64_t value) :
        Component(value) {}
};

#endif //INCLUDE_DATETIME_DATECOMPONENT_H
