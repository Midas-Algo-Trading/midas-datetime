#ifndef DATETIME_DATE_H
#define DATETIME_DATE_H


#include "components/Year.h"
#include "components/Month.h"
#include "components/Day.h"
#include "../Horologe.h"

class Date : public Horologe
{
public:
        friend std::ostream &operator<<(std::ostream &os, const Date &date);

        Year year;
        Month month;
        Day day;

public:
        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        explicit Date(int year=0, int month=0, int day=0) :
                year(Year(year, this)),
                month(Month(month, this)),
                day(Day(day, this)) {}

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        static Date today();
};


#endif //DATETIME_DATE_H
