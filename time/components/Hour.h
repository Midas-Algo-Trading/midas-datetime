#ifndef DATETIME_HOUR_H
#define DATETIME_HOUR_H

#include "../../Component.h"

class Hour : public Component
{
public:
        explicit Hour(int hour) : Component(hour) {}
};

#endif //DATETIME_HOUR_H
