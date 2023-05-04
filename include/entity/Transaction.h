#ifndef __Transaction_h__
#define __Transaction_h__

#include <string>
#include <vector>

#include "TransactionInput.cpp"
#include "TransactionOutput.cpp"

class Transaction
{
    public:
    // Constructors
    Transaction();

    // Utility methods
    std::string to_string();
    void from_string(std::string input);
    std::string to_hash();

    // Getters
    std::string get_ID();
    unsigned int get_input_count();
    std::vector<TransactionInput *> get_transaction_inputs();
    unsigned int get_output_length();
    std::vector<TransactionOutput *> get_transaction_outputs();
    unsigned int get_timestamp();
    float get_fees();
    unsigned int get_size();
    unsigned int get_block_height();
    unsigned int get_confirmations();

    // Setters
    void set_ID(std::string ID);
    void set_input_count(unsigned int input_count);
    void set_transaction_inputs(std::vector<TransactionInput *> transaction_inputs);
    void set_output_length(unsigned int output_count);
    void set_transaction_outputs(std::vector<TransactionOutput *> transaction_outputs);
    void set_timestamp(unsigned int timestamp);
    void set_fees(float fees);
    void set_size(unsigned int size);
    void set_block_height(unsigned int block_height);
    void set_confirmations(unsigned int confirmations);

    private:

    // Hash of transaction
    std::string ID;

    unsigned int input_count;
    std::vector<TransactionInput *> transactionInputs;
    unsigned int output_length;
    std::vector<TransactionOutput *> transactionOutputs;

    // NOT INCLUDED IN CALCULATION OF ID

    unsigned int timestamp;
    float fees;
    unsigned int size;
    unsigned int block_height;
    unsigned int confirmations;
};

#endif