#ifndef __TRANSACTION_CPP__
#define __TRANSACTION_CPP__

#include "Transaction.h"

#include <string>
#include <vector>
#include <chrono>

#include "crypto/ECC.cpp"
#include "entity/TransactionInput.cpp"
#include "entity/TransactionOutput.cpp"
#include "utility/type-conversion.cpp"

//! Constructors
//* - Non-default constructor and deconstructor
//*  + ECC instance pointer
// [
// Non-default constructor
Transaction::Transaction(ECC * ecc)
{
    this->ecc = ecc;
}
// Deconstructor
Transaction::~Transaction()
{
    this->ecc = NULL;
}
// ]

//! ID
//* - The double hash of the transaction data
// [
// Utility
void Transaction::calculate_ID()
{
    std::string output = "";
    output += this->formatted_input_count;
    for (unsigned int z = 0; z < this->input_count; z++)
    {
        output += this->transaction_inputs[z]->to_string();
    }
    output += this->formatted_output_count;
    for (unsigned int z = 0; z < this->output_count; z++)
    {
        std::string transaction_output_string = this->transaction_outputs[z]->to_string();
        transaction_output_string.pop_back();
        output += transaction_output_string;
    }
    this->ID = ecc->hash(ecc->hash(output));
}
// Getters
std::string Transaction::get_ID()
{
    return this->ID;
}
// Setters
void Transaction::set_ID(std::string ID)
{
    this->ID = ID;
}
// ]

//! Input count
//* - The number of transactionInputs
// [
// Getters
unsigned int Transaction::get_input_count()
{
    return this->input_count;
}
std::string Transaction::get_formatted_input_count()
{
    return this->formatted_input_count;
}
// Setters
void Transaction::set_input_count(unsigned int input_count)
{
    this->input_count = input_count;
    this->formatted_input_count = unsigned_int_to_decimal_string(input_count);
}
void Transaction::set_formatted_input_count(std::string formatted_input_count)
{
    this->formatted_input_count = formatted_input_count;
    this->input_count = decimal_string_to_unsigned_int(formatted_input_count);
}
// ]

//! Transaction inputs
//* - Vector of transactionInput pointers
// [
// Getters
std::vector<TransactionInput *> Transaction::get_transaction_inputs()
{
    return this->transaction_inputs;
}
// Setters
void Transaction::set_transaction_inputs(std::vector<TransactionInput *> transaction_inputs)
{
    this->transaction_inputs = transaction_inputs;
}
// Add, remove, clear
void Transaction::add_transaction_input(TransactionInput * transaction_input)
{
    this->transaction_inputs.push_back(transaction_input);
}
void Transaction::remove_transaction_input(unsigned int index)
{
    this->transaction_inputs.erase(this->transaction_inputs.begin() + index);
}
void Transaction::clear_transaction_inputs()
{
    this->transaction_inputs.clear();
}
// ]

//! Output count
//* - The number of transactionOutputs
// [
// Getters
unsigned int Transaction::get_output_count()
{
    return this->output_count;
}
std::string Transaction::get_formatted_output_count()
{
    return this->formatted_output_count;
}
// Setters
void Transaction::set_output_count(unsigned int output_count)
{
    this->output_count = output_count;
    this->formatted_output_count = unsigned_int_to_decimal_string(output_count);
}
void Transaction::set_formatted_output_count(std::string formatted_output_count)
{
    this->formatted_output_count = formatted_output_count;
    this->output_count = decimal_string_to_unsigned_int(formatted_output_count);
}
// ]

//! Output transactions
//* - Vector of transactionOutput pointers
// [
// Getters
std::vector<TransactionOutput *> Transaction::get_transaction_outputs()
{
    return this->transaction_outputs;
}
// Setters
void Transaction::set_transaction_outputs(std::vector<TransactionOutput *> transaction_outputs)
{
    this->transaction_outputs = transaction_outputs;
}
// Add, remove, clear
void Transaction::add_transaction_output(TransactionOutput * transaction_output)
{
    this->transaction_outputs.push_back(transaction_output);
}
void Transaction::remove_transaction_output(unsigned int index)
{
    this->transaction_outputs.erase(this->transaction_outputs.begin() + index);
}
void Transaction::clear_transaction_outputs()
{
    this->transaction_outputs.clear();
}
// ]

//? Begin meta information

//! Timestamp
//* - When the transaction was created
// [
// Utility
void Transaction::set_timestamp_now()
{
    this->set_timestamp(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}
// Getters
unsigned int Transaction::get_timestamp()
{
    return this->timestamp;
}
std::string Transaction::get_formatted_timestamp()
{
    return this->formatted_timestamp;
}
// Setters
void Transaction::set_timestamp(unsigned int timestamp)
{
    this->timestamp = timestamp;
    this->formatted_timestamp = unsigned_int_to_decimal_string(timestamp);
}
void Transaction::set_formatted_timestamp(std::string formatted_timestamp)
{
    this->formatted_timestamp = formatted_timestamp;
    this->timestamp = decimal_string_to_unsigned_int(formatted_timestamp);
}
// ]

//! Fees
//* - Calculated fees (delta between input and output transactions)
// [
// Utility
void Transaction::calculate_fees()
{
    // TODO
}
// Getters
unsigned int Transaction::get_fees()
{
    return this->fees;
}
std::string Transaction::get_formatted_fees()
{
    return this->formatted_fees;
}
// Setters
void Transaction::set_fees(unsigned int fees)
{
    this->fees = fees;
    this->formatted_fees = unsigned_int_to_decimal_string(fees);
}
void Transaction::set_formatted_fees(std::string formatted_fees)
{
    this->formatted_fees = formatted_fees;
    this->fees = decimal_string_to_unsigned_int(formatted_fees);
}
// ]

//! Size
//* - Size of transaction object (used in consideration of fees)
// [
// Utility
void Transaction::calculate_size()
{
    // TODO
}
// Getters
unsigned int Transaction::get_size()
{
    return this->size;
}
std::string Transaction::get_formatted_size()
{
    return this->formatted_size;
}
// Setters
void Transaction::set_size(unsigned int size)
{
    this->size = size;
    this->formatted_size = unsigned_int_to_decimal_string(size);
}
void Transaction::set_formatted_size(std::string formatted_size)
{
    this->formatted_size = formatted_size;
    this->size = decimal_string_to_unsigned_int(formatted_size);
}
// ]

#endif