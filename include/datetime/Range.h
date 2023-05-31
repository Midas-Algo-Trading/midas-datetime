#ifndef DATETIME_RANGE_H
#define DATETIME_RANGE_H

/**
 * Range of 'T'.
 *
 * @tparam T Type of object to have a range of.
 */
template<typename T>
struct Range
{
    /**
     * Start of the range.
     */
    T start;

    /**
     * End of the range.
     */
    T end;

    /**
     * Creates a 'Range' with the range being between 'start' and 'end'.
     * @param start start of the 'Range'.
     * @param end end of the 'Range'.
     */
    Range(T start, T end) :
        start(start),
        end(end)
    {
        if (start > end)
            throw std::invalid_argument("Start must be less than or equal to end");
    }

    /**
     * Checks if 't' is in the range of this 'Range'.
     *
     * @param t object to check
     *
     * @return 'true' if 't' is in range, 'false' otherwise.
     */
    bool in_range(T t) const
    {
        return t >= start && t <= end;
    }
};

#endif //DATETIME_RANGE_H
