#ifndef DATETIME_MONTH_H
#define DATETIME_MONTH_H


#include "../DateComponent.h"

class Month : public DateComponent
{
private:
        static int COMPONENT_IDX;

public:
        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Month(int days, Horologe* owner) : DateComponent(days, COMPONENT_IDX, owner) {}

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;

        int max_days() const;
};


#endif //DATETIME_MONTH_H
