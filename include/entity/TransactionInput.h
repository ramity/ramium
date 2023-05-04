#ifndef __TransactionInput_h__
#define __TransactionInput_h__

#include <string>
#include <vector>

class TransactionInput
{
    public:
    // Constructors
    TransactionInput();

    // Utility methods
    std::string to_string();
    void from_string(std::string input);

    private:

    // The block ID that contains the TransactionOutput being used as a TransactionInput
    std::string ref_block_ID;
    // The transaction ID that contains the TransactionOutput being used as a TransactionInput
    std::string ref_transaction_ID;
    // The index of the TransactionOutput being used as a TransactionInput
    unsigned int ref_transaction_output_index;

    // Index of TransactionInput in Transaction->transactionInputs vector
    unsigned int index;
    // Amount that this TransactionInput holds
    float amount;

    // Number of public keys
    unsigned int public_key_count;
    // Vector containing public keys
    std::vector<std::string> public_keys;
    // Number of signatures
    unsigned int signature_count;
    // Vector containing signatures
    std::vector<std::string> signatures;

};

#endif