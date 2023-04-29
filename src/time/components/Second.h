#ifndef DATETIME_SECOND_H
#define DATETIME_SECOND_H

#include "TimeComponent.h"

class Second : public TimeComponent
{
public:
        explicit Second(int second) : TimeComponent(second) {}
};

#endif //DATETIME_SECOND_H
