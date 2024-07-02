#ifndef DATETIME_MACROS_H
#define DATETIME_MACROS_H

#define ASSERT(condition, exception) \
    do { \
        if (!(condition)) { \
            throw exception; \
        } \
    } while (false)

#endif //DATETIME_MACROS_H
