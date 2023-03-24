#ifndef DATETIME_MONTH_H
#define DATETIME_MONTH_H

class Month
{
public:
        friend class Date;
private:
        //////////////////////////////////////////////////
        // Fields
        //////////////////////////////////////////////////

        int month{};
        Date *owner{};

public:

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        [[nodiscard]] int max_days() const;

        //////////////////////////////////////////////////
        // Operators
        //////////////////////////////////////////////////

        operator int() const;

        Month operator++(int);
        Month operator--(int);
        Month operator+=(int change_amount);
        Month operator-=(int change_amount);

private:
        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Month(int month, Date *owner);

        Month() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        void change_value(int change_by);

        void inc(int inc_amount);

        void dec(int dec_amount);
};


#endif//DATETIME_MONTH_H
