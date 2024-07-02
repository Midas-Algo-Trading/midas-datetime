#ifndef DATETIME_INVALID_STATE_ERROR_H
#define DATETIME_INVALID_STATE_ERROR_H

#include <stdexcept>

class invalid_state_error : public std::runtime_error
{
public:
        explicit invalid_state_error(const std::string& message) :
                std::runtime_error(message) {}
};

#endif //DATETIME_INVALID_STATE_ERROR_H
