#ifndef DATETIME_DAY_H
#define DATETIME_DAY_H

class Day
{
public:
        friend class Date;

private:
        //////////////////////////////////////////////////
        // Fields
        //////////////////////////////////////////////////

        int day{};
        Date *owner{};

public:
        //////////////////////////////////////////////////
        // Operators
        //////////////////////////////////////////////////

        operator int() const;

        Day operator++(int);
        Day operator--(int);
        Day operator+=(int change_amount);
        Day operator-=(int change_amount);

private:
        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Day(int day, Date *owner);

        Day() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        void change_value(int change_by);

        void inc(int inc_amount);

        void dec(int dec_amount);
};

#endif//DATETIME_DAY_H
