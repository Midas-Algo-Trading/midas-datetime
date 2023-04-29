#ifndef DATETIME_MILLISECOND_H
#define DATETIME_MILLISECOND_H

#include "TimeComponent.h"

class Millisecond : public TimeComponent
{
public:
        explicit Millisecond(int millisecond) : TimeComponent(millisecond) {}
};

#endif //DATETIME_MILLISECOND_H
