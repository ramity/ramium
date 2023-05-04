#include "TransactionInput.h"

#include <string>

#include "crypto/Hash.cpp"

TransactionInput::TransactionInput()
{

}

std::string TransactionInput::to_string()
{
    std::string output;

    // TODO

    return output;
}

std::string TransactionInput::to_hash()
{
    return sha512(this->to_string());
}


std::string TransactionInput::get_ref_block_hash()
{
    return this->ref_block_hash;
}

std::string TransactionInput::get_ref_transaction_hash()
{
    return this->ref_transaction_hash;
}

unsigned int TransactionInput::get_ref_transaction_index()
{
    return this->ref_transaction_index;
}

std::string TransactionInput::get_hash()
{
    return this->hash;
}

std::string TransactionInput::get_ref_public_key()
{
    return this->ref_public_key;
}

std::string TransactionInput::get_signature()
{
    return this->signature;
}

void TransactionInput::set_ref_block_hash(std::string ref_block_hash)
{
    this->ref_block_hash = ref_block_hash;
}

void TransactionInput::set_ref_transaction_hash(std::string ref_transaction_hash)
{
    this->ref_transaction_hash = ref_transaction_hash;
}

void TransactionInput::set_ref_transaction_index(unsigned int ref_transaction_index)
{
    this->ref_transaction_index = ref_transaction_index;
}

void TransactionInput::set_hash(std::string hash)
{
    this->hash = hash;
}

void TransactionInput::set_ref_public_key(std::string ref_public_key)
{
    this->ref_public_key = ref_public_key;
}

void TransactionInput::set_signature(std::string signature)
{
    this->signature = signature;
}
