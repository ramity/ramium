#include "TransactionOutput.h"

#include <string>
#include <vector>

#include "utility/type-conversion.cpp"

TransactionOutput::TransactionOutput()
{

}

std::string TransactionOutput::to_string()
{
    std::string output = "";
    output += std::to_string(unsigned_int_to_hex_string(this->index));
    output += std::to_string(unsigned_int_to_hex_string(this->amount));
    output += std::to_string(unsigned_int_to_hex_string(this->public_key_hash_count));
    for (unsigned int z = 0; z < this->public_key_hash_count; z++)
    {
        output += public_key_hashes[z];
    }
    output += this->spent ? '1' : '0';
}

void TransactionOutput::from_string(std::string input)
{
    this->index = hex_string_to_unsigned_int(intput.substr(0, 8));
    this->amount = hex_string_to_unsigned_int(intput.substr(8, 8));
    this->public_key_hash_count = hex_string_to_unsigned_int(intput.substr(16, 8));

    unsigned int start = 24;
    unsigned int size = 88;
    this->clear_public_key_hashes();
    for (unsigned int z = 0; z < this->public_key_hash_count; z++)
    {
        this->add_public_key_hash(input.substr(start, size))
        start += size;
    }

    this->spent = input.substr(start, 1) ? true : false;
}

// Getters
unsigned int TransactionOutput::get_index()
{
    return this->index;
}

unsigned int TransactionOutput::get_amount()
{
    return this->amount;
}

unsigned int TransactionOutput::get_public_key_hash_count()
{
    return this->public_key_hash_count;
}

std::vector<std::string> TransactionOutput::get_public_key_hashes()
{
    return this->public_key_hashes;
}

bool TransactionOutput::get_spent()
{
    return this->spent;
}

// Setters
void TransactionOutput::set_index(unsigned int index)
{
    this->index = index;
}

void TransactionOutput::set_amount(unsigned int amount)
{
    this->amount = amount;
}

void TransactionOutput::set_public_key_hash_count(unsigned int public_key_hash_count)
{
    this->public_key_hash_count = public_key_hash_count;
}

void TransactionOutput::set_public_key_hashes(std::vector<std::string> public_key_hashes)
{
    this->public_key_hashes = public_key_hashes;
}

void TransactionOutput::set_spent(bool spent)
{
    this->spent = spent;
}

// Add, remove, clear
void TransactionOutput::add_public_key_hash(std::string public_key_hash)
{
    this->public_key_hashes.push_back(public_key_hash);
}

void TransactionOutput::remove_public_key_hash(unsigned int index)
{
    this->public_key_hashes.erase(index);
}

void TransactionOutput::clear_public_key_hashes()
{
    this->public_key_hashes.clear();
}
