#include "Hash.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

std::string sha256(std::string input)
{
    std::stringstream stream;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX hash_object;
    SHA256_Init(&hash_object);
    SHA256_Update(&hash_object, input.c_str(), input.size());
    SHA256_Final(hash, &hash_object);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        stream << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
    }

    return stream.str();
}

std::string sha512(std::string input)
{
    std::stringstream stream;
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX hash_object;
    SHA512_Init(&hash_object);
    SHA512_Update(&hash_object, input.c_str(), input.size());
    SHA512_Final(hash, &hash_object);

    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++)
    {
        stream << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
    }

    return stream.str();
}