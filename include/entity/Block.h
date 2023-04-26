#ifndef __Block_h__
#define __Block_h__

#include <string>
#include <vector>

#include "Transaction.cpp"

class Block
{
    public:
    Block(int index, std::string previous_hash, std::string hash, std::string nonce, std::vector<Transaction *> data);

    // getters
    int get_index();
    std::string get_previous_hash();
    std::string get_hash();
    std::string get_nonce();
    std::vector<Transaction *> get_data();

    // setters
    void set_index(int index);
    void set_previous_hash(std::string previous_hash);
    void set_hash(std::string hash);
    void set_nonce(std::string nonce);
    void set_data(vector<Transaction *> data);

    private:
    int index;
    std::string previous_hash;
    std::string hash;
    std::string nonce;
    vector<Transaction *> data;
}

#endif