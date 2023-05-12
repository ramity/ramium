#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>
#include <vector>
#include <iostream>

#include "crypto/ECC.cpp"
#include "Transaction.cpp"

// Format:
// (private)
// properties
// (public)
// utility methods
// getters
// setters
// add, remove, clear

class Block
{
    //! Constructors
    //* - Non-default constructor and deconstructor
    //*  + ECC instance pointer
    // [
    private:
        // Properties
        ECC * ecc;
    public:
        // Non-default constructor
        Block(ECC * ecc);
        // Deconstructor
        ~Block();
    // ]

    //! Mining methods
    //* - Supported:
    //*  + proof of work
    //* - Planned:
    //*  + proof of stake
    // [
    public:
        bool proof_of_work();
    // ]

    //! Previous block hash
    //* - Hash to previous block in chain
    // [
    private:
        // Properties
        std::string previous_block_hash;
    public:
        // Getters
        std::string get_previous_block_hash();
        // Setters
        void set_previous_block_hash(std::string previous_block_hash);
    // ]

    //! Merkle root
    //* - The root hash of the calculated merkle tree
    // [
    private:
        // Properties
        std::string merkle_root;
    public:
        // Getters
        std::string get_merkle_root();
        // Setters
        void set_merkle_root(std::string merkle_root);
    // ]

    //! Timestamp
    //* - When the block entity is created prior to mining process
    // [
    private:
        // Properties
        unsigned int timestamp;
        std::string formatted_timestamp;
    public:
        // Utility
        void set_timestamp_now();
        // Getters
        unsigned int get_timestamp();
        std::string get_formatted_timestamp();
        // Setters
        void set_timestamp(unsigned int timestamp);
        void set_formatted_timestamp(std::string formatted_timestamp);
    // ]

    //! Difficulty target
    //* - The target hash to be equal or less than the produced hash for the PoW calculation
    // [
    private:
        // Properties
        std::string difficulty_target;
    public:
        // Getters
        std::string get_difficulty_target();
        // Setters
        void set_difficulty_target(std::string difficulty_target);
    // ]

    //! Preamble
    //* - (previous block hash + merkle root + formatted timestamp)
    // [
    private:
        // Properties
        std::string preamble;
    public:
        // Utility
        void calculate_preamble();
        // Getters
        std::string get_preamble();
        // Setters
        void set_preamble(std::string preamble);
    // ]

    //! Nonce
    //* - Used to modify hash of block to meet PoW difficulty requirement
    // [
    private:
        // Properties
        unsigned int nonce;
        std::string formatted_nonce;
    public:
        // Getters
        unsigned int get_nonce();
        std::string get_formatted_nonce();
        // Setters
        void set_nonce(unsigned int nonce);
        void set_formatted_nonce(std::string formatted_nonce);
    // ]

    //! Header
    //* - Concatenation of the preamble + formatted nonce
    // [
    private:
        // Properties
        std::string header;
    public:
        // Utility
        void calculate_header();
        // Getters
        std::string get_header();
        // Setters
        void set_header(std::string block_header);
    // ]

    //! ID
    //* - The double hash of the block header
    // [
    private:
        // Properties
        std::string ID;
    public:
        // Utility
        void calculate_ID();
        // Getters
        std::string get_ID();
        // Setters
        void set_ID(std::string ID);
    // ]

    //! Next block hash
    //* - The hash that connects to the next block in the chain
    // [
    private:
        // Properties
        std::string next_block_hash;
    public:
        // Getters
        std::string get_next_block_hash();
        // Setters
        void set_next_block_hash(std::string next_block_hash);
    // ]

    //! Size
    //* - Block size of all hashed properties in bytes
    // [
    private:
        // Properties
        unsigned int size;
        std::string formatted_size;
    public:
        // Getters
        unsigned int get_size();
        std::string get_formatted_size();
        // Setters
        void set_size(unsigned int size);
        void set_formatted_size(std::string formatted_size);
    // ]

    //! Height
    //* - Height of block in chain
    // [
    private:
        // Properties
        unsigned int height;
        std::string formatted_height;
    public:
        // Getters
        unsigned int get_height();
        std::string get_formatted_height();
        // Setters
        void set_height(unsigned int height);
        void set_formatted_height(std::string formatted_height);
    // ]

    //! Chainwork
    //* - The total amount of work that has been done to generate this block and all previous blocks in the blockchain
    // [
    private:
        // Properties
        unsigned int chainwork;
        std::string formatted_chainwork;
    public:
        // Getters
        unsigned int get_chainwork();
        std::string get_formatted_chainwork();
        // Setters
        void set_chainwork(unsigned int chainwork);
        void set_formatted_chainwork(std::string formatted_chainwork);
    // ]

    //! Confirmations
    //* - The number of blocks that come after this block. Incremented after each block
    // [
    private:
        // Properties
        unsigned int confirmations;
        std::string formatted_confirmations;
    public:
        // Getters
        unsigned int get_confirmations();
        std::string get_formatted_confirmations();
        // Setters
        void set_confirmations(unsigned int confirmations);
        void set_formatted_confirmations(std::string formatted_confirmations);
    // ]

    //! Transaction count
    //* - The number of Transaction objects contained by this block
    // [
    private:
        // Properties
        unsigned int transaction_count;
        std::string formatted_transaction_count;
    public:
        // Getters
        unsigned int get_transaction_count();
        std::string get_formatted_transaction_count();
        // Setters
        void set_transaction_count(unsigned int transaction_count);
        void set_formatted_transaction_count(std::string formatted_transaction_count);
    // ]

    //! Transactions
    //* - Vector of Transaction objects contained by this block
    // [
    private:
        // Properties
        std::vector<Transaction *> transactions;
    public:
        // Getters
        std::vector<Transaction *> get_transactions();
        // Setters
        void set_transactions(std::vector<Transaction *> transactions);
        // Add, remove, clear
        void add_transaction(Transaction * transaction);
        void remove_transaction(unsigned int index);
        void clear_transactions();
    // ]

    //! Transaction IDs
    //* - Vector of transaction IDs, used for the calculation of the merkle tree
    // [
    private:
        // Properties
        std::vector<std::string> transaction_IDs;
    public:
        // Utility
        void build_transaction_IDs();
        // Getters
        std::vector<std::string> get_transaction_IDs();
        // Setters
        void set_transaction_IDs(std::vector<std::string> transaction_IDs);
        // Add, remove, clear
        void add_transaction_ID(std::string transaction_ID);
        void remove_transaction_ID(unsigned int index);
        void clear_transaction_IDs();
    // ]

    //! Merkle tree
    //* - merkle_tree stored in breadth-first traversal with size 2n-1 where n is the number of items in transactions
    // [
    private:
        // Properties
        std::vector<std::string> merkle_tree;
    public:
        // Utility
        void build_merkle_tree();
        void print_merkle_tree();
        // Getters
        std::vector<std::string> get_merkle_tree();
        // Setters
        void set_merkle_tree(std::vector<std::string> merkle_tree);
        // Add, remove, clear
        void add_merkle_tree_leaf(std::string leaf);
        void remove_merkle_tree_leaf(unsigned int index);
        void clear_merkle_tree();
    // ]
};

#endif