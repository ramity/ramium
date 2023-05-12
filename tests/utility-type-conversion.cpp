#include <string>

#include "utility/type-conversion.cpp"

int main()
{
    unsigned int max_input = 4294967295;
    std::string max_expected_output = "4294967295";
    std::string max_obtained_output = unsigned_int_to_decimal_string(max_input);
    if (max_expected_output != max_obtained_output)
    {
        return 1;
    }

    std::string leading_zeros_input = "0000000001";
    unsigned int leading_zeros_expected_output = 1;
    unsigned int leading_zeros_obtained_output = decimal_string_to_unsigned_int(leading_zeros_input);
    if (leading_zeros_expected_output != leading_zeros_obtained_output)
    {
        return 1;
    }

    return 0;
}