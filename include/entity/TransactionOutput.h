#ifndef __TRANSACTION_OUTPUT_H__
#define __TRANSACTION_OUTPUT_H__

#include <string>
#include <vector>

class TransactionOutput
{
    public:
    // Constructors
    TransactionOutput();

    // Utility methods
    std::string to_string();
    void from_string(std::string input);

    // Getters
    unsigned int get_index();
    unsigned int get_amount();
    unsigned int get_public_key_hash_count();
    std::vector<std::string> get_public_key_hashes();
    bool get_spent();

    // Setters
    void set_index(unsigned int index);
    void set_amount(unsigned int amount);
    void set_public_key_hash_count(unsigned int public_key_hash_count);
    void set_public_key_hashes(std::vector<std::string> public_key_hashes);
    void set_spent(bool spent);

    // Add, remove, clear
    void add_public_key_hash(std::string public_key_hash);
    void remove_public_key_hash(unsigned int index);
    void clear_public_key_hashes();

    private:

    // Index of TransactionOutput in Transaction->transactionOuputs vector
    unsigned int  index;
    // Amount that this TransactionOutput holds
    unsigned int amount;
    // Number of public key hashes
    unsigned int  public_key_hash_count;
    // Vector containing public key hashes
    std::vector<std::string> public_key_hashes;

    // NOT INCLUDED IN CALCULATION OF ID

    // Marked true when a valid TransactionInput references this TransactionOutput 
    bool spent;
};

#endif