#ifndef __HASH_H__
#define __HASH_H__

#include <string>

std::string sha256(std::string input);
std::string sha512(std::string input);

#endif