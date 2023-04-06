#ifndef DATETIME_DAY_H
#define DATETIME_DAY_H


#include "../DateComponent.h"

class Day : public DateComponent
{
private:
        static int COMPONENT_IDX;

public:
        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Day(int days, Date* owner) : DateComponent(days, COMPONENT_IDX, owner) {}

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;
};


#endif //DATETIME_DAY_H
