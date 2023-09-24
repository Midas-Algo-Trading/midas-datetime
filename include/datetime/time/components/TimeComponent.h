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
        ASSERT(value <= std::numeric_limits<int>::max(),
               fmt::format("TimeComponent value: {} is too large. Max size is {}",
                           value, std::numeric_limits<int>::max()));
    }
};

#endif //DATETIME_TIMECOMPONENT_H
