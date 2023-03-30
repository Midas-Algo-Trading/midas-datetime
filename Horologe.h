#ifndef DATETIME_HOROLOGE_H
#define DATETIME_HOROLOGE_H


#include <vector>
#include "DatetimeComponent.h"

class DatetimeComponent;

class Horologe
{
protected:
        std::vector<DatetimeComponent*> component_hierarchy;

public:
        DatetimeComponent get_component_by_idx(int idx) const;
};


#endif //DATETIME_HOROLOGE_H
