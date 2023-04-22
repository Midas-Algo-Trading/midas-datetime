#ifndef DATETIME_SECOND_H
#define DATETIME_SECOND_H

#include "../../Component.h"

class Second : public Component
{
public:
        explicit Second(int second) : Component(second) {}
};

#endif //DATETIME_SECOND_H
