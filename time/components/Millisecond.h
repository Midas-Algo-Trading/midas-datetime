#ifndef DATETIME_MILLISECOND_H
#define DATETIME_MILLISECOND_H

#include "../../Component.h"

class Millisecond : public Component
{
public:
        explicit Millisecond(int millisecond) : Component(millisecond) {}
};

#endif //DATETIME_MILLISECOND_H
