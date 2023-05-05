#ifndef __TRANSACTION_INPUT_H__
#define __TRANSACTION_INPUT_H__

#include <string>
#include <vector>

#include "crypto/ECC.cpp"

class TransactionInput
{
    public:
    // Constructors
    TransactionInput();

    // Utility methods
    std::string to_string();
    void from_string(std::string input);

    // Getters
    std::string get_ref_block_ID();
    std::string get_ref_transaction_ID();
    unsigned int get_ref_transaction_output_index();
    unsigned int get_index();
    unsigned int get_public_key_count();
    std::vector<std::string> get_public_keys();
    unsigned int get_signature_count();
    std::vector<std::string> get_signatures();

    // Setters
    void set_ref_block_ID(std::string ref_block_ID);
    void set_ref_transaction_ID(std::string ref_transaction_ID);
    void set_ref_transaction_output_index(unsigned int ref_transaction_output_index);
    void set_index(unsigned int index);
    void set_public_key_count(unsigned int public_key_count);
    void set_public_keys(std::vector<std::string> public_keys);
    void set_signature_count(unsigned int signature_count);
    void set_signatures(std::vector<std::string> signatures);

    // Add, remove, clear
    void add_public_key(std::string public_key);
    void remove_public_key(unsigned int index);
    void clear_public_keys();

    void add_signature(std::string signature);
    void remove_signature(unsigned int index);
    void clear_signatures();

    // Hash to be signed
    std::string create_signature_input(ECC * ecc, unsigned int public_key_index);
    std::string create_signature(ECC * ecc, unsigned int public_key_index);

    private:

    // The block ID that contains the TransactionOutput being used as a TransactionInput
    std::string ref_block_ID;
    // The transaction ID that contains the TransactionOutput being used as a TransactionInput
    std::string ref_transaction_ID;
    // The index of the TransactionOutput being used as a TransactionInput
    unsigned int ref_transaction_output_index;

    // Index of TransactionInput in Transaction->transactionInputs vector
    unsigned int index;

    // Number of public keys
    unsigned int public_key_count;
    // The unhashed public keys on the ref. TransactionOutput in preserved order
    std::vector<std::string> public_keys;
    // Number of signatures
    unsigned int signature_count;
    // The signatures that sign this TransactionInput using the privateKeys associated
    // with the public keys referenced on the TransactionOutput in preserved order  
    std::vector<std::string> signatures;

};

#endif