#include "year.h"

//////////////////////////////////////////////////
// Public Constructors
//////////////////////////////////////////////////

Year::Year(int year) : year(year) {}

//////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////

bool Year::is_leap_year() const
{
        if (year % 4 != 0)
        {
                return false;
        }
        else if (year % 100 != 0)
        {
                return true;
        }
        else if (year % 400 != 0)
        {
                return false;
        }
        else
        {
                return true;
        }
}

//////////////////////////////////////////////////
// Public Operators
//////////////////////////////////////////////////

Year::operator int() const
{
        return year;
}

Year Year::operator++(int)
{
        year++;
        return *this;
}

Year Year::operator--(int)
{
        year--;
        return *this;
}

Year Year::operator+=(int change_amount)
{
        year += change_amount;
        return *this;
}

Year Year::operator-=(int change_amount)
{
        year -= change_amount;
        return *this;
}

