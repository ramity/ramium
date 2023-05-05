#ifndef __RSA_CIPHER_H__
#define __RSA_CIPHER_H__

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string>

class RSACipher
{
    private:
    // Config
    int key_length;
    int public_exponent;
    int modulus_size;
    std::string public_key_path;
    std::string private_key_path;

    // Interal values
    RSA * rsa_object;
    BIGNUM * bne;
    unsigned char * plaintext;
    unsigned char * ciphertext;
    unsigned char * signature;
    unsigned int plaintext_length;
    unsigned int ciphertext_length;
    unsigned int signature_length;

    public:
    // Constructors
    RSACipher();
    RSACipher(int key_length);
    RSACipher(int key_length, int public_exponent);
    RSACipher(int key_length, int public_exponent, std::string public_key_path, std::string private_key_path);
    ~RSACipher();

    void set_public_key_path(std::string path);
    void set_private_key_path(std::string path);
    std::string get_public_key_path();
    std::string get_private_key_path();

    void generate_keys();
    void read_keys();
    void write_keys();

    std::string get_plaintext();
    std::string get_ciphertext();
    std::string get_signature();

    void set_plaintext(std::string plaintext);
    void set_ciphertext(std::string ciphertext);
    void set_signature(std::string signature);

    void encrypt();
    void decrypt();
    void sign();
    int verify();
};

#endif