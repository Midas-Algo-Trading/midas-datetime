#ifndef DATETIME_DATETIMECOMPONENT_H
#define DATETIME_DATETIMECOMPONENT_H


#include <variant>
#include "Horologe.h"
#include "util/exceptions/NotImplementedException.h"

class DatetimeComponent
{
private:
        friend class Horologe;

protected:
        //////////////////////////////////////////////////
        // Fields
        //////////////////////////////////////////////////

        int value{};

        int component_idx{};

        Horologe* owner{};

public:
        //////////////////////////////////////////////////
        // Operators
        //////////////////////////////////////////////////

        DatetimeComponent operator++(int);
        DatetimeComponent operator--(int);
        DatetimeComponent operator+=(int change_amount);
        DatetimeComponent operator-=(int change_amount);

        operator int() const;

protected:
        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        DatetimeComponent(int value, int component_idx, Horologe* owner) :
                value(value), component_idx(component_idx), owner(owner) {}

        DatetimeComponent() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        virtual int max_value() { throw NotImplementedException(); }

        virtual int min_value() { throw NotImplementedException(); }

        virtual void inc(int inc_amount);

        virtual void dec(int dec_amount);

private:
        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        void change_value(int change_amount);
};


#endif //DATETIME_DATETIMECOMPONENT_H
