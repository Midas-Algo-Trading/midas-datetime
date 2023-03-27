#ifndef DATETIME_DATETIMECOMPONENT_H
#define DATETIME_DATETIMECOMPONENT_H


class DatetimeComponent
{
protected:
        //////////////////////////////////////////////////
        // Fields
        //////////////////////////////////////////////////

        int value{};

        int component_idx{};

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

        DatetimeComponent(int value, int component_idx) : value(value), component_idx(component_idx) {}

        DatetimeComponent() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        virtual int max_value() { return 0;}

        virtual int min_value() { return 0;}

private:
        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        void change_value(int change_amount);

private:
        //////////////////////////////////////////////////
        // Virtual Methods
        //////////////////////////////////////////////////

        virtual void inc(int inc_amount) {}

        virtual void dec(int dec_amount) {}
};


#endif //DATETIME_DATETIMECOMPONENT_H
