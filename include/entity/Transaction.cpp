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

Transaction::Transaction()
{

}

// Utility methods
std::string Transaction::to_string()
{
    std::string output = "";
    output += unsigned_int_to_hex_string(this->input_count);
    for (unsigned int z = 0; z < this->input_count; z++)
    {
        output += this->transaction_inputs[z]->to_string();
    }
    output += unsigned_int_to_hex_string(this->output_count);
    for (unsigned int z = 0; z < this->output_count; z++)
    {
        output += this->transaction_outputs[z]->to_string();
    }
    output += unsigned_int_to_hex_string(this->timestamp);
    output += unsigned_int_to_hex_string(this->fees);
    output += unsigned_int_to_hex_string(this->size);
    output += unsigned_int_to_hex_string(this->block_height);
    output += unsigned_int_to_hex_string(this->confirmations);
    return output;
}

void Transaction::from_string(std::string input)
{

}

void Transaction::set_timestamp_now()
{
    this->timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Transaction::calculate_ID(ECC * ecc)
{
    std::string output = "";
    output += unsigned_int_to_hex_string(this->input_count);
    for (unsigned int z = 0; z < this->input_count; z++)
    {
        output += this->transaction_inputs[z]->to_string();
    }
    output += unsigned_int_to_hex_string(this->output_count);
    for (unsigned int z = 0; z < this->output_count; z++)
    {
        std::string transaction_output_string = this->transaction_outputs[z]->to_string();
        transaction_output_string.pop_back();
        output += transaction_output_string;
    }
    this->ID = ecc->encode(ecc->hash(output));
}


// Getters
std::string Transaction::get_ID()
{
    return this->ID;
}

unsigned int Transaction::get_input_count()
{
    return this->input_count;
}

std::vector<TransactionInput *> Transaction::get_transaction_inputs()
{
    return this->transaction_inputs;
}

unsigned int Transaction::get_output_count()
{
    return this->output_count;
}

std::vector<TransactionOutput *> Transaction::get_transaction_outputs()
{
    return this->transaction_outputs;
}

unsigned int Transaction::get_timestamp()
{
    return this->timestamp;
}

unsigned int Transaction::get_fees()
{
    return this->fees;
}

unsigned int Transaction::get_size()
{
    return this->size;
}

unsigned int Transaction::get_block_height()
{
    return this->block_height;
}

unsigned int Transaction::get_confirmations()
{
    return this->confirmations;
}

// Setters
void Transaction::set_ID(std::string ID)
{
    this->ID = ID;
}

void Transaction::set_input_count(unsigned int input_count)
{
    this->input_count = input_count;
}

void Transaction::set_transaction_inputs(std::vector<TransactionInput *> transaction_inputs)
{
    this->transaction_inputs = transaction_inputs;
}

void Transaction::set_output_count(unsigned int output_count)
{
    this->output_count = output_count;
}

void Transaction::set_transaction_outputs(std::vector<TransactionOutput *> transaction_outputs)
{
    this->transaction_outputs = transaction_outputs; 
}

void Transaction::set_timestamp(unsigned int timestamp)
{
    this->timestamp = timestamp;
}

void Transaction::set_fees(unsigned int fees)
{
    this->fees = fees;
}

void Transaction::set_size(unsigned int size)
{
    this->size = size;
}

void Transaction::set_block_height(unsigned int block_height)
{
    this->block_height = block_height;
}

void Transaction::set_confirmations(unsigned int confirmations)
{
    this->confirmations = confirmations;
}

// Add, erase, clear
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

#endif