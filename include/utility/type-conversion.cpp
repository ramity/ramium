#ifndef __TYPE_CONVERSION_CPP__
#define __TYPE_CONVERSION_CPP__

#include <iomanip>
#include <sstream>

std::string unsigned_int_to_hex_string(unsigned int input)
{
    std::stringstream output;
    output << std::hex << std::setw(8) << std::setfill('0') << input;
    return output.str();
}

unsigned int hex_string_to_unsigned_int(std::string input)
{
    unsigned int output;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> output;
    return output;
}

std::string unsigned_int_to_decimal_string(unsigned int input)
{
    std::stringstream output;
    output << std::setw(10) << std::setfill('0') << input;
    return output.str();
}

unsigned int decimal_string_to_unsigned_int(std::string input)
{
    unsigned int output;
    std::stringstream ss;
    ss << input;
    ss >> output;
    return output;
}

#endif