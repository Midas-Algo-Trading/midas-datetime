#ifndef DATETIME_NOTIMPLEMENTEDERROR_H
#define DATETIME_NOTIMPLEMENTEDERROR_H

#include <stdexcept>

class NotImplementedError : public std::logic_error
{
public:
        explicit NotImplementedError(const std::string& message) :
                std::logic_error(message) {}
};

#endif //DATETIME_NOTIMPLEMENTEDERROR_H
