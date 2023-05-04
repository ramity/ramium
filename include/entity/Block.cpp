#include "Block.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>

#include "crypto/Hash.cpp"

Block::Block()
{

}

void Block::build_transaction_hashes()
{
    // Make sure transactions has been populated
    assert(this->transactions.size() != 0 && "transactions must be populated");

    this->transaction_hashes = std::vector<std::string>(this->transactions.size());

    for (unsigned int z = 0; z < this->transactions.size(); z++)
    {
        this->transaction_hashes.push_back(this->transactions[z]->to_string());
    }
}

void Block::build_merkle_tree()
{
    // Make sure transaction_hashes has been populated
    assert(this->transaction_hashes.size() != 0 && "transaction_hashes must be populated");

    // Copy into local var (we may have to duplicate the last element)
    this->merkle_tree = this->transaction_hashes;
    int start = 0;
    int levels = ceil(log2(this->merkle_tree.size()));

    // Compute the parent hashes iteratively until there's only one hash left
    for (int i = 0; i < levels; i++)
    {
        // If the level is odd, duplicate the last hash
        if (this->merkle_tree.size() % 2 != 0)
        {
            this->merkle_tree.push_back(this->merkle_tree.back());
        }

        int level_size = this->merkle_tree.size();

        // Construct the new level of the tree
        for (int j = start; j < level_size; j += 2)
        {
            std::string left_hash = this->merkle_tree[j];
            std::string right_hash = this->merkle_tree[j+1];
            std::string combined_hash = sha512(left_hash + right_hash);
            this->merkle_tree.push_back(combined_hash);
        }

        start = level_size;
    }

    // Set merkle root hash
    this->merkle_root = this->merkle_tree.back();
}

void Block::print_merkle_tree()
{
    // Make sure merkle_tree has been populated
    assert(this->merkle_tree.size() != 0 && "merkle_tree must be populated");

    int level = 0;
    int levelSize = 1;
    for (int i = this->merkle_tree.size() - 1; i >= 0; i--)
    {
        std::cout << this->merkle_tree[i] << " ";
        if (++level == levelSize)
        {
            levelSize *= 2;
            level = 0;
            std::cout << std::endl;
        }
    }
}

// getters included in hash

unsigned int Block::get_size()
{
    return this->size;
}

unsigned int Block::get_height()
{
    return this->height;
}

std::string Block::get_previous_hash()
{
    return this->previous_hash;
}

std::string Block::get_nonce()
{
    return this->nonce;
}

std::string Block::get_difficulty()
{
    return this->difficulty;
}

unsigned long Block::get_timestamp()
{
    return this->timestamp;
}

std::vector<std::string> Block::get_transaction_hashes()
{
    return transaction_hashes;
}

std::string Block::get_merkle_root()
{
    return this->merkle_root;
}

// setters included in hash

void Block::set_size(unsigned int size)
{
    this->size = size;
}

void Block::set_height(unsigned int height)
{
    this->height = height;
}

void Block::set_previous_hash(std::string previous_hash)
{
    this->previous_hash = previous_hash;
}

void Block::set_nonce(std::string nonce)
{
    this->nonce = nonce;
}

void Block::set_difficulty(std::string difficulty)
{
    this->difficulty = difficulty;
}

void Block::set_timestamp(unsigned long timestamp)
{
    this->timestamp = timestamp;
}

void Block::set_transaction_hashes(std::vector<std::string> transaction_hashes)
{
    this->transaction_hashes = transaction_hashes;
}

void Block::set_merkle_root(std::string merkle_root)
{
    this->merkle_root = merkle_root;
}

// getters not included in hash

std::vector<Transaction *> Block::get_transactions()
{
    return this->transactions;
}

unsigned int Block::get_chainwork()
{
    return this->chainwork;
}

std::string Block::get_hash()
{
    return this->hash;
}

std::string Block::get_next_hash()
{
    return this->next_hash;
}

unsigned int Block::get_confirmations()
{
    return this->confirmations;
}

std::vector<std::string> Block::get_merkle_tree()
{
    return this->merkle_tree;
}


// setters not included in hash

void Block::set_transactions(std::vector<Transaction *> transactions)
{
    this->transactions = transactions;
}

void Block::set_chainwork(unsigned int chainwork)
{
    this->chainwork = chainwork;
}

void Block::set_hash(std::string hash)
{
    this->hash = hash;
}

void Block::set_next_hash(std::string next_hash)
{
    this->next_hash = next_hash;
}

void Block::set_confirmations(unsigned int confirmations)
{
    this->confirmations = confirmations;
}

void Block::set_merkle_tree(std::vector<std::string> merkle_tree)
{
    this->merkle_tree = merkle_tree;
}
