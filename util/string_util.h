//
// Created by Erik on 3/3/2023.
//

#ifndef DATETIME_STRING_UTIL_H
#define DATETIME_STRING_UTIL_H

#include <string>

static std::string pad(const std::string &str, int target_length, char pad_char, bool pad_left)
{
        std::string padded_str = str;

        int num_pad_chars = target_length - str.length();
        std::string pad_chars(num_pad_chars, pad_char);
        if (pad_left)
        {
                padded_str = pad_chars + padded_str;
        }
        else
        {
                padded_str = padded_str + pad_chars;
        }

        return padded_str;
}

static std::string lpad(const std::string &str, int target_length, char pad_char)
{
        return pad(str, target_length, pad_char, true);
}

static std::string rpad(const std::string &str, int target_length, char pad_char)
{
        return pad(str, target_length, pad_char, false);
}


#endif//DATETIME_STRING_UTIL_H
