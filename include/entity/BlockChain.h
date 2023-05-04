#ifndef __Transaction_h__
#define __Transaction_h__

#include <string>
#include <vector>

#include "Block.cpp"

class BlockChain
{
    public:
    BlockChain();

    //

    private:

    std::vector blocks<Block *>;

    std::string inputs;
    std::string outputs;
    std::string fees;
    std::string locktime;
    std::string message_hash;
    std::string signature;

    std::string transaction_hash;

    // to add:
    // input_length
    // output_length
};

#endif