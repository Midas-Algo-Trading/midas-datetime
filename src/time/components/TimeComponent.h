#ifndef DATETIME_TIMECOMPONENT_H
#define DATETIME_TIMECOMPONENT_H

#include "../../Component.h"

class TimeComponent : public Component
{
public:
        explicit TimeComponent(int value) : Component(value) {}
};

#endif //DATETIME_TIMECOMPONENT_H
