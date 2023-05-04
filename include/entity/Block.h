#ifndef __Block_h__
#define __Block_h__

#include <string>
#include <vector>
#include <iostream>
#include <chrono>

#include "Transaction.cpp"

class Block
{
    public:

    Block();
    void build_transaction_hashes();
    void build_merkle_tree();
    void print_merkle_tree();

    // getters included in hash
    unsigned int get_size();
    unsigned int get_height();
    std::string get_previous_hash();
    std::string get_nonce();
    std::string get_difficulty();
    unsigned long get_timestamp();
    std::vector<std::string> get_transaction_hashes();
    std::string get_merkle_root();

    // setters included in hash
    void set_size(unsigned int size);
    void set_height(unsigned int height);
    void set_previous_hash(std::string previous_hash);
    void set_nonce(std::string nonce);
    void set_difficulty(std::string difficulty);
    void set_timestamp(unsigned long timestamp);
    void set_transaction_hashes(std::vector<std::string> transaction_hashes);
    void set_merkle_root(std::string merkle_root);

    // getters not included in hash
    std::vector<Transaction *> get_transactions();
    unsigned int get_chainwork();
    std::string get_hash();
    std::string get_next_hash();
    unsigned int get_confirmations();
    std::vector<std::string> get_merkle_tree();

    // setters not included in hash
    void set_transactions(std::vector<Transaction *> transactions);
    void set_chainwork(unsigned int chainwork);
    void set_hash(std::string hash);
    void set_next_hash(std::string next_hash);
    void set_confirmations(unsigned int confirmations);
    void set_merkle_tree(std::vector<std::string> merkle_tree);

    private:

    // Properties included in the calculation of the block hash

    // Block size of all hashed properties in bytes
    unsigned int size;
    // Height of block in chain
    unsigned int height;
    // Hash to previous block in chain
    std::string previous_hash;
    // Used to modify hash of block to meet PoW difficulty requirement
    std::string nonce;
    // The target hash to be equal or less than the produced hash for the PoW calculation
    std::string difficulty;
    // When block is solved prior to submission to other nodes
    unsigned long timestamp; // = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    // Vector of hashes of transactions, used for the calculation of the merkle tree
    std::vector<std::string> transaction_hashes;
    // The root hash of the calculated merkle tree
    std::string merkle_root;

    // Properties not included in the calculation of the block hash

    // Vector of Transaction objects contained by this block
    std::vector<Transaction *> transactions;
    // The total amount of work that has been done to generate this block and all previous blocks in the blockchain
    unsigned int chainwork;
    // The hash of this block
    std::string hash;
    // The hash that connects to the next block in the chain
    std::string next_hash;
    // The number of blocks that come after this block. Incremented after each block
    unsigned int confirmations;
    // merkle_tree stored in breadth-first traversal with size 2n-1 where n is the number of items in transactions
    std::vector<std::string> merkle_tree;
};

#endif