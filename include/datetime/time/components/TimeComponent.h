#ifndef DATETIME_TIMECOMPONENT_H
#define DATETIME_TIMECOMPONENT_H

#include "datetime/Component.h"

/**
 * Component for 'Time'.
 */
struct TimeComponent : Component
{
    /**
     * Creates a 'TimeComponent' whose 'value' matches 'value'.
     *
     * @param value value to have the newly created 'TimeComponent' set to.
     */
    explicit TimeComponent(uint32_t value) :
        Component(value) {}
};

#endif //DATETIME_TIMECOMPONENT_H
