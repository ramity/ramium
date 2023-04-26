#include "key.h"

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

void Key::print_error()
{
    fprintf(stderr, "[x] %s\n", strerror(errno));
}

Key::Key()
{
    this->bne = BN_new();

    if (BN_set_word(this->bne, this->public_exponent) != 1)
    {
        this->print_error();
    }

    this->init_rsa_object();
}

bool Key::generate_key_pair()
{
    if (RSA_generate_key_ex(this->rsa_object, this->key_length, this->bne, NULL) != 1)
    {
        this->print_error();
        return false;
    }

    return true;
}

bool Key::write_public_key_file()
{
    FILE * fp = fopen(this->public_key_file_path, "w");

    if (fp == NULL)
    {
        this->print_error();
        return false;
    }

    if (PEM_write_RSAPublicKey(fp, this->rsa_object) == 0)
    {
        this->print_error();
        return false;
    }

    fclose(fp);
    return true;
}

bool Key::write_private_key_file()
{
    FILE * fp = fopen(this->private_key_file_path, "w");

    if (fp == NULL)
    {
        this->print_error();
        return false;
    }

    if (PEM_write_RSAPrivateKey(fp, this->rsa_object, NULL, NULL, 0, NULL, NULL) == 0)
    {
        this->print_error();
        return false;
    }

    fclose(fp);
    return true;
}

bool Key::read_public_key_file()
{
    FILE * fp = fopen(this->public_key_file_path, "rb");

    if (fp == NULL)
    {
        this->print_error();
        return false;
    }

    if (PEM_read_RSAPublicKey(fp, &this->rsa_object, NULL, NULL) == NULL)
    {
        this->print_error();
        return false;
    }

    fclose(fp);
    return true;
}

bool Key::read_private_key_file()
{
    FILE * fp = fopen(this->private_key_file_path, "rb");

    if (fp == NULL)
    {
        this->print_error();
        return false;
    }

    if (PEM_read_RSAPrivateKey(fp, &this->rsa_object, NULL, NULL) == NULL)
    {
        this->print_error();
        return false;
    }

    fclose(fp);
    return true;
}

void Key::init_rsa_object()
{
    this->rsa_object = RSA_new();
}

bool Key::init_plaintext(int size)
{
    this->plaintext = (unsigned char *) malloc(size);

    if (this->plaintext == NULL)
    {
        this->print_error();
        return false;
    }

    memset(this->plaintext, 0, size);
    return true;
}

bool Key::init_ciphertext()
{
    int modulus_size = RSA_size(this->rsa_object);
    this->ciphertext = (unsigned char *) malloc(modulus_size);

    if (this->ciphertext == NULL)
    {
        this->print_error();
        return false;
    }

    memset(this->ciphertext, 0, modulus_size);
    return true;
}

// void Key::init_buffers()
// {
//     this->init_plaintext();
//     this->init_ciphertext();
// }

// void Key::init()
// {
//     this->init_rsa_object();
//     this->init_buffers();
// }

void Key::free_rsa_object()
{
    RSA_free(this->rsa_object);
}

void Key::free_plaintext()
{
    free(this->plaintext);
}

void Key::free_ciphertext()
{
    free(this->ciphertext);
}

void Key::free_buffers()
{
    this->free_plaintext();
    this->free_ciphertext();
}

// void Key::free()
// {
//     this->free_rsa_object();
//     this->free_buffers();
// }

int Key::public_encrypt(unsigned char * message)
{
    int message_length = strlen((const char *) message) + 1;
    return RSA_public_encrypt(message_length, message, this->ciphertext, this->rsa_object, RSA_PKCS1_OAEP_PADDING);
}

int Key::private_decrypt(int size)
{
    return RSA_private_decrypt(size, this->ciphertext, this->plaintext, this->rsa_object, RSA_PKCS1_OAEP_PADDING);
}