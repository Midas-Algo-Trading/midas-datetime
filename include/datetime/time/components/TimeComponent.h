#ifndef DATETIME_TIMECOMPONENT_H
#define DATETIME_TIMECOMPONENT_H

#include "datetime/Component.h"
#include "../../../../util/macros.h"
#include "fmt/format.h"

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
        Component(value)
    {
        ASSERT(value <= 2147483648,
               fmt::format("TimeComponent value: {} is too large. Max size is {}",
                           value, 2147483648));
    }
};

#endif //DATETIME_TIMECOMPONENT_H
