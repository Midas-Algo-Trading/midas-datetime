#include "month.h"
#include "../date.h"

//////////////////////////////////////////////////
// Public Constructors
//////////////////////////////////////////////////

Month::Month(int month, Date *owner) : month(month), owner(owner) {}

//////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////

int Month::max_days() const
{
        switch (month)
        {
                case 2:
                        return owner->year.is_leap_year() ? 29 : 28;
                case 4:
                case 6:
                case 9:
                case 11:
                        return 30;
                default:
                        return 31;
        }
}

//////////////////////////////////////////////////
// Public Operators
//////////////////////////////////////////////////

Month::operator int() const
{
        return month;
}

Month Month::operator++(int)
{
        change_value(1);
        return *this;
}

Month Month::operator--(int)
{
        change_value(-1);
        return *this;
}

Month Month::operator+=(int change_amount)
{
        change_value(change_amount);
        return *this;
}

Month Month::operator-=(int change_amount)
{
        change_value(change_amount);
        return *this;
}

//////////////////////////////////////////////////
// Private Methods
//////////////////////////////////////////////////

void Month::change_value(int change_by)
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

void Month::inc(int inc_amount)
{
       for (int i = 0; i < inc_amount; i++)
       {
               month++;

               // Update year if need be
               if (month > 12)
               {
                       owner->year++;
                       month = 1;
               }
       }
}

void Month::dec(int dec_amount)
{
        for (int i = 0; i < abs(dec_amount); i++)
        {
                month--;

                // Update year if need be
                if (month < 1)
                {
                        owner->year--;
                        month = 12;
                }
        }
}