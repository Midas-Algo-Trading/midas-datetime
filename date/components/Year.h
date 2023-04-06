#ifndef DATETIME_YEAR_H
#define DATETIME_YEAR_H


#include "../DateComponent.h"

class Year : DateComponent
{
private:
        static int COMPONENT_IDX;

public:
        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        explicit Year(int years, Horologe* owner) : DateComponent(years, COMPONENT_IDX, owner) {}

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;

        bool is_leap_year() const;
};


#endif //DATETIME_YEAR_H
