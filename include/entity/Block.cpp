#ifndef __BLOCK_CPP__
#define __BLOCK_CPP__

#include "Block.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>

Block::Block()
{

}

void Block::build_transaction_IDs()
{
    // Make sure transactions has been populated
    assert(this->transactions.size() != 0 && "transactions must be populated");

    this->transaction_IDs = std::vector<std::string>(this->transactions.size());

    for (unsigned int z = 0; z < this->transactions.size(); z++)
    {
        this->transaction_IDs[z] = this->transactions[z]->get_ID();
    }
}

void Block::build_merkle_tree(ECC * ecc)
{
    // Make sure transaction_IDs has been populated
    assert(this->transaction_IDs.size() != 0 && "transaction_IDs must be populated");

    this->merkle_tree = this->transaction_IDs;
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
            std::string combined_hash = ecc->encode(ecc->hash(left_hash + right_hash));
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
        // std::cout << i << " ";
        // std::cout << this->merkle_tree[i] << " ";
        std::cout << this->merkle_tree[i].substr(0, 8) << " ";
        if (++level == levelSize)
        {
            levelSize *= 2;
            level = 0;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

// Getters
std::string Block::get_previous_block_hash()
{
    return this->previous_block_hash;
}

std::string Block::get_merkle_root()
{
    return this->merkle_root;
}

unsigned int Block::get_timestamp()
{
    return this->timestamp;
}

std::string Block::get_difficulty_target()
{
    return this->difficulty_target;
}

unsigned int Block::get_nonce()
{
    return this->nonce;
}

std::string Block::get_ID()
{
    return this->ID;
}

std::string Block::get_next_block_hash()
{
    return this->next_block_hash;
}

unsigned int Block::get_size()
{
    return this->size;
}

unsigned int Block::get_height()
{
    return this->height;
}

unsigned int Block::get_chainwork()
{
    return this->chainwork;
}

unsigned int Block::get_confirmations()
{
    return this->confirmations;
}

unsigned int Block::get_transaction_count()
{
    return this->transaction_count;
}

std::vector<Transaction *> Block::get_transactions()
{
    return this->transactions;
}

std::vector<std::string> Block::get_transaction_IDs()
{
    return this->transaction_IDs;
}

std::vector<std::string> Block::get_merkle_tree()
{
    return this->merkle_tree;
}


// Setters
void Block::set_previous_block_hash(std::string previous_block_hash)
{
    this->previous_block_hash = previous_block_hash;
}

void Block::set_merkle_root(std::string merkle_root)
{
    this->merkle_root = merkle_root;
}

void Block::set_timestamp(unsigned int timestamp)
{
    this->timestamp = timestamp;
}

void Block::set_difficulty_target(std::string difficulty_target)
{
    this->difficulty_target = difficulty_target;
}

void Block::set_nonce(unsigned int nonce)
{
    this->nonce = nonce;
}

void Block::set_ID(std::string ID)
{
    this->ID = ID;
}

void Block::set_next_block_hash(std::string next_block_hash)
{
    this->next_block_hash = next_block_hash;
}

void Block::set_size(unsigned int size)
{
    this->size = size;
}

void Block::set_height(unsigned int height)
{
    this->height = height;
}

void Block::set_chainwork(unsigned int chainwork)
{
    this->chainwork = chainwork;
}

void Block::set_confirmations(unsigned int confirmations)
{
    this->confirmations = confirmations;
}

void Block::set_transaction_count(unsigned int transaction_count)
{
    this->transaction_count = transaction_count;
}

void Block::set_transactions(std::vector<Transaction *> transactions)
{
    this->transactions = transactions;
}

void Block::set_transaction_IDs(std::vector<std::string> transaction_IDs)
{
    this->transaction_IDs = transaction_IDs;
}

void Block::set_merkle_tree(std::vector<std::string> merkle_tree)
{
    this->merkle_tree = merkle_tree;
}


// Add, remove, clear
void Block::add_transaction(Transaction * transaction)
{
    this->transactions.push_back(transaction);
}

void Block::remove_transaction(unsigned int index)
{
    this->transactions.erase(this->transactions.begin() + index);
}

void Block::clear_transactions()
{
    this->transactions.clear();
}

void Block::add_transaction_ID(std::string transaction_ID)
{
    this->transaction_IDs.push_back(transaction_ID);
}

void Block::remove_transaction_ID(unsigned int index)
{
    this->transaction_IDs.erase(this->transaction_IDs.begin() + index);
}

void Block::clear_transaction_IDs()
{
    this->transaction_IDs.clear();
}

void Block::add_merkle_tree(std::string hash)
{
    this->merkle_tree.push_back(hash);
}

void Block::remove_merkle_tree(unsigned int index)
{
    this->merkle_tree.erase(this->merkle_tree.begin() + index);
}

void Block::clear_merkle_tree()
{
    this->merkle_tree.clear();
}

#endif