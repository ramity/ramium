#ifndef __TRANSACTION_INPUT_CPP__
#define __TRANSACTION_INPUT_CPP__

#include "TransactionInput.h"

#include <string>
#include <vector>

#include "utility/type-conversion.cpp"
#include "crypto/ECC.cpp"

TransactionInput::TransactionInput()
{
    
}

std::string TransactionInput::to_string()
{
    std::string output = "";
    output += this->ref_block_ID;
    output += this->ref_transaction_ID;
    output += unsigned_int_to_hex_string(this->ref_transaction_output_index);
    output += unsigned_int_to_hex_string(this->index);
    output += unsigned_int_to_hex_string(this->public_key_count);
    for (unsigned int z = 0; z < this->public_key_count; z++)
    {
        output += this->public_keys[z];
    }
    output += unsigned_int_to_hex_string(this->signature_count);
    for (unsigned int z = 0; z < this->signature_count; z++)
    {
        output += this->signatures[z];
    }
    return output;
}

void TransactionInput::from_string(std::string input)
{
    this->ref_block_ID = input.substr(0, 88);
    this->ref_transaction_ID = input.substr(88, 88);
    this->ref_transaction_output_index = hex_string_to_unsigned_int(input.substr(176, 8));
    this->index = hex_string_to_unsigned_int(input.substr(184, 8));
    this->public_key_count = hex_string_to_unsigned_int(input.substr(192, 8));

    unsigned int start = 200;
    unsigned int size = 212;
    this->clear_public_keys();
    for (unsigned int z = 0; z < this->public_key_count; z++)
    {
        this->add_public_key(input.substr(start, size));
        start += size;
    }

    this->signature_count = hex_string_to_unsigned_int(input.substr(start, 8));
    start += 8;
    size = 176;
    this->clear_signatures();
    for (unsigned int z = 0; z < this->signature_count; z++)
    {
        this->add_signature(input.substr(start, size));
        start += size;
    }
}

// Getters
std::string TransactionInput::get_ref_block_ID()
{
    return this->ref_block_ID;
}

std::string TransactionInput::get_ref_transaction_ID()
{
    return this->ref_transaction_ID;
}

unsigned int TransactionInput::get_ref_transaction_output_index()
{
    return this->ref_transaction_output_index;
}

unsigned int TransactionInput::get_index()
{
    return this->index;
}

unsigned int TransactionInput::get_public_key_count()
{
    return this->public_key_count;
}

std::vector<std::string> TransactionInput::get_public_keys()
{
    return this->public_keys;
}

unsigned int TransactionInput::get_signature_count()
{
    return this->signature_count;
}

std::vector<std::string> TransactionInput::get_signatures()
{
    return this->signatures;
}

// Setters
void TransactionInput::set_ref_block_ID(std::string ref_block_ID)
{
    this->ref_block_ID = ref_block_ID;
}

void TransactionInput::set_ref_transaction_ID(std::string ref_transaction_ID)
{
    this->ref_transaction_ID = ref_transaction_ID;
}

void TransactionInput::set_ref_transaction_output_index(unsigned int ref_transaction_output_index)
{
    this->ref_transaction_output_index = ref_transaction_output_index;
}

void TransactionInput::set_index(unsigned int index)
{
    this->index = index;
}

void TransactionInput::set_public_key_count(unsigned int public_key_count)
{
    this->public_key_count = public_key_count;
}

void TransactionInput::set_public_keys(std::vector<std::string> public_keys)
{
    this->public_keys = public_keys;
}

void TransactionInput::set_signature_count(unsigned int signature_count)
{
    this->signature_count = signature_count;
}

void TransactionInput::set_signatures(std::vector<std::string> signatures)
{
    this->signatures = signatures;
}

// Add, remove, clear
void TransactionInput::add_public_key(std::string public_key)
{
    this->public_keys.push_back(public_key);
}

void TransactionInput::remove_public_key(unsigned int index)
{
    this->public_keys.erase(this->public_keys.begin() + index);
}

void TransactionInput::clear_public_keys()
{
    this->public_keys.clear();
}

void TransactionInput::add_signature(std::string signature)
{
    this->signatures.push_back(signature);
}

void TransactionInput::remove_signature(unsigned int index)
{
    this->signatures.erase(this->signatures.begin() + index);
}

void TransactionInput::clear_signatures()
{
    this->signatures.clear();
}

// Hash to be signed
std::string TransactionInput::create_signature_input(ECC * ecc, unsigned int public_key_index)
{
    std::string output = "";
    output += this->ref_block_ID;
    output += this->ref_transaction_ID;
    output += unsigned_int_to_hex_string(this->ref_transaction_output_index);
    output += unsigned_int_to_hex_string(this->index);
    output += ecc->hash(this->public_keys[public_key_index]);
    ecc->hash(ecc->hash(output));
    return output;
}

std::string TransactionInput::create_signature(ECC * ecc, unsigned int public_key_index)
{
    ecc->set_raw_plaintext_hash(this->create_signature_input(ecc, public_key_index));
    ecc->sign();
    return ecc->get_encoded_signature();
}

#endif