#ifndef DATETIME_DATE_H
#define DATETIME_DATE_H

#include "components/day.h"
#include "components/month.h"
#include "components/year.h"
#include <chrono>
#include <iostream>

class Date
{
public:
        friend std::ostream &operator<<(std::ostream &os, const Date &date);

        //////////////////////////////////////////////////
        // Fields
        //////////////////////////////////////////////////

        Year year;
        Month month;
        Day day;

        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        // Defaults to today's date
        Date();

        Date(int year, int month, int day);


        //////////////////////////////////////////////////
        // Operators
        //////////////////////////////////////////////////

        Date operator++(int);
        Date operator--(int);
        Date operator+=(int change_amount);
        Date operator-=(int change_amount);
};

#endif//DATETIME_DATE_H
