#include "RSACipher.h"

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>
#include <string>

#include "Base64.cpp"

RSACipher::RSACipher()
{
    // Config
    this->key_length = 4096;
    this->public_exponent = 65537;
    this->modulus_size = this->key_length / 8;
    this->set_public_key_path("/root/ramium/data/public_key");
    this->set_private_key_path("/root/ramium/data/private_key");

    // Init
    this->rsa_object = RSA_new();
    this->bne = BN_new();
    BN_set_word(this->bne, this->public_exponent);

    this->plaintext_length = this->modulus_size;
    this->ciphertext_length = this->modulus_size;
    this->signature_length = this->modulus_size;

    this->plaintext = new unsigned char[this->plaintext_length];
    this->ciphertext = new unsigned char[this->ciphertext_length];
    this->signature = new unsigned char[this->signature_length];
}

RSACipher::RSACipher(int key_length)
{
    // Config
    this->key_length = key_length;
    this->public_exponent = 65537;
    this->modulus_size = this->key_length / 8;
    this->set_public_key_path("/root/ramium/data/public_key");
    this->set_private_key_path("/root/ramium/data/private_key");

    // Init
    this->rsa_object = RSA_new();
    this->bne = BN_new();
    BN_set_word(this->bne, this->public_exponent);

    this->plaintext_length = this->modulus_size;
    this->ciphertext_length = this->modulus_size;
    this->signature_length = this->modulus_size;

    this->plaintext = new unsigned char[this->plaintext_length];
    this->ciphertext = new unsigned char[this->ciphertext_length];
    this->signature = new unsigned char[this->signature_length];
}

RSACipher::RSACipher(int key_length, int public_exponent)
{
    // Config
    this->key_length = key_length;
    this->public_exponent = public_exponent;
    this->modulus_size = this->key_length / 8;
    this->set_public_key_path("/root/ramium/data/public_key");
    this->set_private_key_path("/root/ramium/data/private_key");

    // Init
    this->rsa_object = RSA_new();
    this->bne = BN_new();
    BN_set_word(this->bne, this->public_exponent);

    this->plaintext_length = this->modulus_size;
    this->ciphertext_length = this->modulus_size;
    this->signature_length = this->modulus_size;

    this->plaintext = new unsigned char[this->plaintext_length];
    this->ciphertext = new unsigned char[this->ciphertext_length];
    this->signature = new unsigned char[this->signature_length];
}

RSACipher::RSACipher(int key_length, int public_exponent, std::string public_key_path, std::string private_key_path)
{
    // Config
    this->key_length = key_length;
    this->public_exponent = public_exponent;
    this->modulus_size = this->key_length / 8;
    this->set_public_key_path(public_key_path);
    this->set_private_key_path(private_key_path);

    // Init
    this->rsa_object = RSA_new();
    this->bne = BN_new();
    BN_set_word(this->bne, this->public_exponent);

    this->plaintext_length = this->modulus_size;
    this->ciphertext_length = this->modulus_size;
    this->signature_length = this->modulus_size;

    this->plaintext = new unsigned char[this->plaintext_length];
    this->ciphertext = new unsigned char[this->ciphertext_length];
    this->signature = new unsigned char[this->signature_length];
}

RSACipher::~RSACipher()
{
    RSA_free(this->rsa_object);
    BN_free(this->bne);

    delete[] plaintext;
    delete[] ciphertext;
    delete[] signature;
}

void RSACipher::set_public_key_path(std::string path)
{
    this->public_key_path = path;
}

void RSACipher::set_private_key_path(std::string path)
{
    this->private_key_path = path;
}

std::string RSACipher::get_public_key_path()
{
    return this->public_key_path;
}

std::string RSACipher::get_private_key_path()
{
    return this->private_key_path;
}

void RSACipher::generate_keys()
{
    RSA_generate_key_ex(this->rsa_object, this->key_length, this->bne, NULL);
}

void RSACipher::read_keys()
{
    FILE * fp;

    fp = fopen(this->public_key_path.c_str(), "rb");
    PEM_read_RSAPublicKey(fp, &this->rsa_object, NULL, NULL);
    fclose(fp);

    fp = fopen(this->private_key_path.c_str(), "rb");
    PEM_read_RSAPrivateKey(fp, &this->rsa_object, NULL, NULL);
    fclose(fp);
}

void RSACipher::write_keys()
{
    FILE * fp;

    fp = fopen(this->public_key_path.c_str(), "wb");
    PEM_write_RSAPublicKey(fp, this->rsa_object);
    fclose(fp);

    fp = fopen(this->private_key_path.c_str(), "wb");
    PEM_write_RSAPrivateKey(fp, this->rsa_object, NULL, NULL, 0, NULL, NULL);
    fclose(fp);
}

std::string RSACipher::get_plaintext()
{
    return std::string(reinterpret_cast<const char*>(this->plaintext));
}

std::string RSACipher::get_ciphertext()
{
    return base64_encode(reinterpret_cast<const unsigned char*>(this->ciphertext), this->ciphertext_length);
}

std::string RSACipher::get_signature()
{
    return base64_encode(reinterpret_cast<const unsigned char*>(this->signature), this->signature_length);
}

void RSACipher::set_plaintext(std::string plaintext)
{
    this->plaintext_length = plaintext.size();
    std::copy(plaintext.begin(), plaintext.end(), this->plaintext);
    this->plaintext[this->plaintext_length] = '\0';
}

void RSACipher::set_ciphertext(std::string ciphertext)
{
    this->ciphertext_length = ciphertext.size();
    std::copy(ciphertext.begin(), ciphertext.end(), this->ciphertext);
    this->ciphertext[this->ciphertext_length] = '\0';
}

void RSACipher::set_signature(std::string signature)
{
    this->signature_length = signature.size();
    std::copy(signature.begin(), signature.end(), this->signature);
    this->signature[this->signature_length] = '\0';
}

void RSACipher::encrypt()
{
    this->ciphertext_length = RSA_public_encrypt(this->plaintext_length, reinterpret_cast<const unsigned char*>(this->plaintext), this->ciphertext, this->rsa_object, RSA_PKCS1_OAEP_PADDING);
}

void RSACipher::decrypt()
{
    this->plaintext_length = RSA_private_decrypt(this->ciphertext_length, this->ciphertext, this->plaintext, this->rsa_object, RSA_PKCS1_OAEP_PADDING);
}

void RSACipher::sign()
{
    RSA_sign(NID_sha512, this->plaintext, this->plaintext_length, this->signature, &this->signature_length, this->rsa_object);
}

int RSACipher::verify()
{
    return RSA_verify(NID_sha512, reinterpret_cast<const unsigned char*>(this->plaintext), this->plaintext_length, this->signature, this->signature_length, this->rsa_object);
}