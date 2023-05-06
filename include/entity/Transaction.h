#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#include <string>
#include <vector>

#include "crypto/ECC.cpp"
#include "entity/TransactionInput.cpp"
#include "entity/TransactionOutput.cpp"

class Transaction
{
    public:
    // Constructors
    Transaction();

    // Utility methods
    std::string to_string();
    void from_string(std::string input);
    void set_timestamp_now();
    void calculate_ID(ECC * ecc);

    // Getters
    std::string get_ID();
    unsigned int get_input_count();
    std::vector<TransactionInput *> get_transaction_inputs();
    unsigned int get_output_count();
    std::vector<TransactionOutput *> get_transaction_outputs();
    unsigned int get_timestamp();
    unsigned int get_fees();
    unsigned int get_size();
    unsigned int get_block_height();
    unsigned int get_confirmations();

    // Setters
    void set_ID(std::string ID);
    void set_input_count(unsigned int input_count);
    void set_transaction_inputs(std::vector<TransactionInput *> transaction_inputs);
    void set_output_count(unsigned int output_count);
    void set_transaction_outputs(std::vector<TransactionOutput *> transaction_outputs);
    void set_timestamp(unsigned int timestamp);
    void set_fees(unsigned int fees);
    void set_size(unsigned int size);
    void set_block_height(unsigned int block_height);
    void set_confirmations(unsigned int confirmations);

    // Add, remove, clear
    void add_transaction_input(TransactionInput * transaction_input);
    void remove_transaction_input(unsigned int index);
    void clear_transaction_inputs();
    void add_transaction_output(TransactionOutput * transaction_output);
    void remove_transaction_output(unsigned int index);
    void clear_transaction_outputs();

    private:

    // Hash of transaction
    std::string ID;

    unsigned int input_count;
    std::vector<TransactionInput *> transaction_inputs;
    unsigned int output_count;
    std::vector<TransactionOutput *> transaction_outputs;

    // NOT INCLUDED IN CALCULATION OF ID

    unsigned int timestamp;
    unsigned int fees;
    unsigned int size;
    unsigned int block_height;
    unsigned int confirmations;
};

#endif