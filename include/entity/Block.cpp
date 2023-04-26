#include "Block.h"

Block::Block(int index, std::string previous_hash, std::string hash, std::string nonce, std::vector<Transaction *> data)
{
    this->index = index;
    this->previous_hash = previous_hash;
    this->hash = hash;
    this->nonce = nonce;
    this->data = data;
}

int Block::get_index()
{
    return this->index;
}

std::string Block::get_previous_hash()
{
    return this->previous_hash;
}

std::string Block::get_hash()
{
    return this->hash;
}

std::string Block::get_nonce()
{
    return this->nonce;
}

std::vector<Transaction *> Block::get_data()
{
    return this->data;
}

void Block::set_index(int index)
{
    this->index = index;
}

void Block::set_previous_hash(std::string previous_hash)
{
    this->previous_hash = previous_hash;
}

void Block::set_hash(std::string hash)
{
    this->hash = hash;
}

void Block::set_nonce(std::string nonce)
{
    this->nonce = nonce;
}

void Block::set_data(std::vector<Transaction *>)
{
    this->data = data;
}