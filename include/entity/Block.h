#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>
#include <vector>
#include <iostream>
#include <chrono>

#include "Transaction.cpp"

class Block
{
    public:

    Block();
    void build_transaction_IDs();
    void build_merkle_tree(ECC * ecc);
    void print_merkle_tree();

    // Getters
    std::string get_previous_block_hash();
    std::string get_merkle_root();
    unsigned int get_timestamp();
    std::string get_difficulty_target();
    unsigned int get_nonce();
    std::string get_ID();
    std::string get_next_block_hash();
    unsigned int get_size();
    unsigned int get_height();
    unsigned int get_chainwork();
    unsigned int get_confirmations();
    unsigned int get_transaction_count();
    std::vector<Transaction *> get_transactions();
    std::vector<std::string> get_transaction_IDs();
    std::vector<std::string> get_merkle_tree();

    // Setters
    void set_previous_block_hash(std::string previous_block_hash);
    void set_merkle_root(std::string merkle_root);
    void set_timestamp(unsigned int timestamp);
    void set_difficulty_target(std::string difficulty_target);
    void set_nonce(unsigned int nonce);
    void set_ID(std::string ID);
    void set_next_block_hash(std::string next_block_hash);
    void set_size(unsigned int size);
    void set_height(unsigned int height);
    void set_chainwork(unsigned int chainwork);
    void set_confirmations(unsigned int confirmations);
    void set_transaction_count(unsigned int transaction_count);
    void set_transactions(std::vector<Transaction *> transactions);
    void set_transaction_IDs(std::vector<std::string> transaction_IDs);
    void set_merkle_tree(std::vector<std::string> merkle_tree);

    // Add, remove, clear
    void add_transaction(Transaction * transaction);
    void remove_transaction(unsigned int index);
    void clear_transactions();
    void add_transaction_ID(std::string transaction_ID);
    void remove_transaction_ID(unsigned int index);
    void clear_transaction_IDs();
    void add_merkle_tree(std::string hash);
    void remove_merkle_tree(unsigned int index);
    void clear_merkle_tree();

    private:

    // Block header

    // Hash to previous block in chain
    std::string previous_block_hash;
    // The root hash of the calculated merkle tree
    std::string merkle_root;
    // When the block entity is created prior to mining process
    unsigned int timestamp; // = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    // The target hash to be equal or less than the produced hash for the PoW calculation
    std::string difficulty_target;
    // Used to modify hash of block to meet PoW difficulty requirement
    unsigned int nonce;

    // Other properties

    // The hash of the block header
    std::string ID;
    // The hash that connects to the next block in the chain
    std::string next_block_hash;
    // Block size of all hashed properties in bytes
    unsigned int size;
    // Height of block in chain
    unsigned int height;
    // The total amount of work that has been done to generate this block and all previous blocks in the blockchain
    unsigned int chainwork;
    // The number of blocks that come after this block. Incremented after each block
    unsigned int confirmations;
    // The number of Transaction objects contained by this block
    unsigned int transaction_count;
    // Vector of Transaction objects contained by this block
    std::vector<Transaction *> transactions;
    // Vector of transaction IDs, used for the calculation of the merkle tree
    std::vector<std::string> transaction_IDs;
    // merkle_tree stored in breadth-first traversal with size 2n-1 where n is the number of items in transactions
    std::vector<std::string> merkle_tree;
};

#endif