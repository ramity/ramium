#ifndef __BLOCK_CPP__
#define __BLOCK_CPP__

#include "Block.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <chrono>

#include "crypto/ECC.cpp"
#include "utility/type-conversion.cpp"

//! Constructors
//* - Non-default constructor and deconstructor
//*  + ECC instance pointer
// [
// Non-default constructor
Block::Block(ECC * ecc)
{
    this->ecc = ecc;
}
// Deconstructor
Block::~Block()
{
    // Clear ecc pointer (memory is assumed to be deleted externally)
    this->ecc = NULL;

    // Delete transaction memory
    for (unsigned int z = 0; z < this->transactions.size(); z++)
    {
        delete this->transactions[z];
    }

    // Clear transaction vector
    this->clear_transactions();
}
// ]

//! Mining methods
//* - Supported:
//*  + proof of work
//* - Planned:
//*  + proof of stake
// [
bool Block::proof_of_work()
{
    // Uses preamble + formatted nonce
    calculate_header();

    // Double hashes header
    calculate_ID();

    // Pull values into local memory
    std::string ID = this->get_ID();
    std::string difficulty_target = this->get_difficulty_target();

    // Iterate over each char in ID and compare values
    for (unsigned int z = 0; z < 64; z++)
    {
        if (+ID[z] > +difficulty_target[z])
        {
            // Use setter to update nonce and formatted nonce
            this->set_nonce(this->nonce + 1);
            return false;
        }
    }

    return true;
}
// ]

//! Previous block hash
//* - Hash to previous block in chain
// [
std::string Block::get_previous_block_hash()
{
    return this->previous_block_hash;
}
void Block::set_previous_block_hash(std::string previous_block_hash)
{
    this->previous_block_hash = previous_block_hash;
}
// ]

//! Merkle root
//* - The root hash of the calculated merkle tree
// [
std::string Block::get_merkle_root()
{
    return this->merkle_root;
}
void Block::set_merkle_root(std::string merkle_root)
{
    this->merkle_root = merkle_root;
}
// ]

//! Timestamp
//* - When the block entity is created prior to mining process
// [
// Utility
void Block::set_timestamp_now()
{
    this->set_timestamp(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}
// Getters
unsigned int Block::get_timestamp()
{
    return this->timestamp;
}
std::string Block::get_formatted_timestamp()
{
    return this->formatted_timestamp;
}
// Setters
void Block::set_timestamp(unsigned int timestamp)
{
    this->timestamp = timestamp;
    this->formatted_timestamp = unsigned_int_to_decimal_string(timestamp);
}
void Block::set_formatted_timestamp(std::string formatted_timestamp)
{
    this->formatted_timestamp = formatted_timestamp;
    this->timestamp = decimal_string_to_unsigned_int(formatted_timestamp);
}
// ]

//! Difficulty target
//* - The target hash to be equal or less than the produced hash for the PoW calculation
// [
// Getters
std::string Block::get_difficulty_target()
{
    return this->difficulty_target;
}
// Setters
void Block::set_difficulty_target(std::string difficulty_target)
{
    this->difficulty_target = difficulty_target;
}
// ]

//! Preamble
//* - (previous block hash + merkle root + formatted timestamp)
// [
// Utility
void Block::calculate_preamble()
{
    this->preamble = this->previous_block_hash + this->merkle_root + this->formatted_timestamp;
}
// Getters
std::string Block::get_preamble()
{
    return this->preamble = preamble;
}
// Setters
void Block::set_preamble(std::string preamble)
{
    this->preamble = preamble;
}
// ]

//! Nonce
//* - Used to modify hash of block to meet PoW difficulty requirement
// [
// Getters
unsigned int Block::get_nonce()
{
    return this->nonce;
}
std::string Block::get_formatted_nonce()
{
    return this->formatted_nonce;
}
// Setters
void Block::set_nonce(unsigned int nonce)
{
    this->nonce = nonce;
    this->formatted_nonce = unsigned_int_to_decimal_string(nonce);
}
void Block::set_formatted_nonce(std::string formatted_nonce)
{
    this->formatted_nonce = formatted_nonce;
    this->nonce = decimal_string_to_unsigned_int(formatted_nonce);
}
// ]

//! Header
//* - Concatenation of the preamble + formatted nonce
// [
// Utility
void Block::calculate_header()
{
    this->header = this->preamble + this->formatted_nonce;
}
// Getters
std::string Block::get_header()
{
    return this->header;
}
// Setters
void Block::set_header(std::string header)
{
    this->header = header;
}
// ]

//! ID
//* - The double hash of the block header
// [
// Utility
void Block::calculate_ID()
{
    this->ID = this->ecc->hash(this->ecc->hash(this->header));
}
// Getters
std::string Block::get_ID()
{
    return this->ID;
}
// Setters
void Block::set_ID(std::string ID)
{
    this->ID = ID;
}
// ]

//! Next block hash
//* - The hash that connects to the next block in the chain
// [
// Getters
std::string Block::get_next_block_hash()
{
    return this->next_block_hash;
}
// Setters
void Block::set_next_block_hash(std::string next_block_hash)
{
    this->next_block_hash = next_block_hash;
}
// ]

//! Size
//* - Block size of all hashed properties in bytes
// [
// Getters
unsigned int Block::get_size()
{
    return this->size;
}
std::string Block::get_formatted_size()
{
    return this->formatted_size;
}
// Setters
void Block::set_size(unsigned int size)
{
    this->size = size;
    this->formatted_size = unsigned_int_to_decimal_string(size);
}
void Block::set_formatted_size(std::string formatted_size)
{
    this->formatted_size = formatted_size;
    this->size = decimal_string_to_unsigned_int(formatted_size);
}
// ]

//! Height
//* - Height of block in chain
// [
// Getters
unsigned int Block::get_height()
{
    return this->height;
}
std::string Block::get_formatted_height()
{
    return this->formatted_height;
}
// Setters
void Block::set_height(unsigned int height)
{
    this->height = height;
    this->formatted_height = unsigned_int_to_decimal_string(height);
}
void Block::set_formatted_height(std::string formatted_height)
{
    this->formatted_height = formatted_height;
    this->height = decimal_string_to_unsigned_int(formatted_height);
}
// ]

//! Chainwork
//* - The total amount of work that has been done to generate this block and all previous blocks in the blockchain
// [
// Getters
unsigned int Block::get_chainwork()
{
    return this->chainwork;
}
std::string Block::get_formatted_chainwork()
{
    return this->formatted_chainwork;
}
// Setters
void Block::set_chainwork(unsigned int chainwork)
{
    this->chainwork = chainwork;
    this->formatted_chainwork = unsigned_int_to_decimal_string(chainwork);
}
void Block::set_formatted_chainwork(std::string formatted_chainwork)
{
    this->formatted_chainwork = formatted_chainwork;
    this->chainwork = decimal_string_to_unsigned_int(formatted_chainwork);
}
// ]

//! Confirmations
//* - The number of blocks that come after this block. Incremented after each block
// [
// Getters
unsigned int Block::get_confirmations()
{
    return this->confirmations;
}
std::string Block::get_formatted_confirmations()
{
    return this->formatted_confirmations;
}
// Setters
void Block::set_confirmations(unsigned int confirmations)
{
    this->confirmations = confirmations;
    this->formatted_confirmations = unsigned_int_to_decimal_string(confirmations);
}
void Block::set_formatted_confirmations(std::string formatted_confirmations)
{
    this->formatted_confirmations = formatted_confirmations;
    this->confirmations = decimal_string_to_unsigned_int(formatted_confirmations);
}
// ]

//! Transaction count
//* - The number of Transaction objects contained by this block
// [
// Getters
unsigned int Block::get_transaction_count()
{
    return this->transaction_count;
}
std::string Block::get_formatted_transaction_count()
{
    return this->formatted_transaction_count;
}
// Setters
void Block::set_transaction_count(unsigned int transaction_count)
{
    this->transaction_count = transaction_count;
    this->formatted_transaction_count = unsigned_int_to_decimal_string(transaction_count);
}
void Block::set_formatted_transaction_count(std::string formatted_transaction_count)
{
    this->formatted_transaction_count = formatted_transaction_count;
    this->transaction_count = decimal_string_to_unsigned_int(formatted_transaction_count);
}
// ]

//! Transactions
//* - Vector of Transaction objects contained by this block
// [
// Getters
std::vector<Transaction *> Block::get_transactions()
{
    return this->transactions;
}
// Setters
void Block::set_transactions(std::vector<Transaction *> transactions)
{
    this->transactions = transactions;
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
// ]

//! Transaction IDs
//* - Vector of transaction IDs, used for the calculation of the merkle tree
// [
// Utility
void Block::build_transaction_IDs()
{
    // Make sure transactions has been populated
    assert(this->transactions.size() != 0 && "transactions must be populated");

    // Init vector with same size as transactions vector
    this->transaction_IDs = std::vector<std::string>(this->transactions.size());

    for (unsigned int z = 0; z < this->transactions.size(); z++)
    {
        this->transaction_IDs[z] = this->transactions[z]->get_ID();
    }
}
// Getters
std::vector<std::string> Block::get_transaction_IDs()
{
    return this->transaction_IDs;
}
// Setters
void Block::set_transaction_IDs(std::vector<std::string> transaction_IDs)
{
    this->transaction_IDs = transaction_IDs;
}
// Add, remove, clear
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
// ]

//! Merkle tree
//* - merkle_tree stored in breadth-first traversal with size 2n-1 where n is the number of items in transactions
// [
// Utility
void Block::build_merkle_tree()
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
            std::string combined_hash = this->ecc->hash(left_hash + right_hash);
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
std::vector<std::string> Block::get_merkle_tree()
{
    return this->merkle_tree;
}
// Setters
void Block::set_merkle_tree(std::vector<std::string> merkle_tree)
{
    this->merkle_tree = merkle_tree;
}
// Add, remove, clear
void Block::add_merkle_tree_leaf(std::string leaf)
{
    this->merkle_tree.push_back(leaf);
}
void Block::remove_merkle_tree_leaf(unsigned int index)
{
    this->merkle_tree.erase(this->merkle_tree.begin() + index);
}
void Block::clear_merkle_tree()
{
    this->merkle_tree.clear();
}
// ]

#endif