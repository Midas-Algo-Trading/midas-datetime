#ifndef DATETIME_DURATION_H
#define DATETIME_DURATION_H

class Duration
{
public:
        uint64_t duration;

        virtual operator int() const
        {
                return duration;
        }
protected:
        explicit Duration(uint64_t nanoseconds) :
                duration(nanoseconds) {}
};

#endif //DATETIME_DURATION_H
