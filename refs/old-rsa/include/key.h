#ifndef __key_h__
#define __key_h__

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

class Key
{
    private:
    RSA * rsa_object;
    BIGNUM * bne;

    int key_length = 8192;
    int public_exponent = 65537;
    char * public_key_file_path = "test_public";
    char * private_key_file_path = "test_private";

    void print_error();

    public:
    unsigned char * plaintext;
    unsigned char * ciphertext;

    Key();

    bool generate_key_pair();

    bool write_public_key_file();
    bool write_private_key_file();

    bool read_public_key_file();
    bool read_private_key_file();

    void init_rsa_object();
    bool init_plaintext(int size);
    bool init_ciphertext();
    // void init_buffers();
    // void init();

    void free_rsa_object();
    void free_plaintext();
    void free_ciphertext();
    void free_buffers();
    // void free();

    int public_encrypt(unsigned char * message);
    int private_decrypt(int size);
};

#endif