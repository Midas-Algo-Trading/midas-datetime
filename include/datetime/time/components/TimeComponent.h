#ifndef DATETIME_TIMECOMPONENT_H
#define DATETIME_TIMECOMPONENT_H

#include "../../../../src/Component.h"
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
    explicit TimeComponent(int64_t value) :
        Component(value) {}

    virtual ~TimeComponent() = default;
};

#endif //DATETIME_TIMECOMPONENT_H
