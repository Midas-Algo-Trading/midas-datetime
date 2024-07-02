#ifndef DATETIME_NOT_IMPLEMENTED_ERROR_H
#define DATETIME_NOT_IMPLEMENTED_ERROR_H

#include <stdexcept>

class not_implemented_error : public std::logic_error
{
public:
        explicit not_implemented_error(const std::string& message) :
                std::logic_error(message) {}
};

#endif //DATETIME_NOT_IMPLEMENTED_ERROR_H
