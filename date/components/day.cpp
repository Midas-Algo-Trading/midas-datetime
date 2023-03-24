#include "../date.h"

//////////////////////////////////////////////////
// Public Constructors
//////////////////////////////////////////////////

Day::Day(int day, Date *owner) : day(day), owner(owner) {}

//////////////////////////////////////////////////
// Public Operators
//////////////////////////////////////////////////

Day::operator int() const
{
        return day;
}

Day Day::operator++(int)
{
        change_value(1);
        return *this;
}

Day Day::operator--(int)
{
        change_value(-1);
        return *this;
}

Day Day::operator+=(int change_amount)
{
        change_value(change_amount);
        return *this;
}

Day Day::operator-=(int change_amount)
{
        change_value(change_amount);
        return *this;
}

//////////////////////////////////////////////////
// Private Methods
//////////////////////////////////////////////////

void Day::change_value(int change_by)
{
        if (change_by >= 0)
        {
                inc(change_by);
        }
        else
        {
                dec(change_by);
        }
}

void Day::inc(int inc_amount)
{
        for (int i = 0; i < inc_amount; i++)
        {
                day++;

                // Update Day if need be
                if (day > owner->month.max_days())
                {
                        owner->month++;
                        day = 1;
                }
        }
}

void Day::dec(int dec_amount)
{
        for (int i = 0; i < abs(dec_amount); i++)
        {
                day--;

                // Update Day if need be
                if (day < 1)
                {
                        owner->month++;
                        day = owner->month.max_days();
                }
        }
}

