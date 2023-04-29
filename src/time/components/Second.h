#ifndef DATETIME_SECOND_H
#define DATETIME_SECOND_H

#include "TimeComponent.h"

struct Second : TimeComponent
{
        explicit Second(int second) : TimeComponent(second) {}
};

#endif //DATETIME_SECOND_H
