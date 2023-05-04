#include <iostream>
#include <iomanip>
#include <sstream>
#include <iomanip>

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