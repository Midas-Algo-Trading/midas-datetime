#ifndef DATETIME_COMPONENT_H
#define DATETIME_COMPONENT_H


class Component
{
private:
        int value;

public:
        explicit Component(int value) : value(value) {}

        operator int() const
        {
                return value;
        }
};

#endif //DATETIME_COMPONENT_H
