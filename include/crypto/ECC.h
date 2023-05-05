#ifndef __ECC_H__
#define __ECC_H__

#include <iostream>
#include <string>
#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/sha.h>

class ECC
{
    private:
    // Config
    std::string public_key_path;
    std::string private_key_path;

    // Interal values
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::ECIES<CryptoPP::ECP>::PrivateKey private_key;
    CryptoPP::ECIES<CryptoPP::ECP>::PublicKey public_key;
    CryptoPP::OID curve;

    std::string output;
    CryptoPP::SHA512 hash_method;
    CryptoPP::StringSink output_sink;
    CryptoPP::Base64Encoder encoder;
    CryptoPP::Base64Decoder decoder;
    CryptoPP::HashFilter hasher;
    CryptoPP::ECIES<CryptoPP::ECP>::Encryptor * encryptor;
    CryptoPP::ECIES<CryptoPP::ECP>::Decryptor * decryptor;
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA512>::Signer * signer;
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA512>::Verifier * verifier;

    CryptoPP::PK_EncryptorFilter * encryptor_filter;
    CryptoPP::PK_DecryptorFilter * decryptor_filter;
    CryptoPP::SignerFilter * signer_filter;
    CryptoPP::SignatureVerificationFilter * verifier_filter; 

    // Plaintext
    std::string raw_plaintext;
    std::string encoded_plaintext;
    std::string raw_plaintext_hash;
    std::string encoded_plaintext_hash;

    // Ciphertext
    std::string raw_ciphertext;
    std::string encoded_ciphertext;
    std::string raw_ciphertext_hash;
    std::string encoded_ciphertext_hash;

    // Signature
    std::string raw_signature;
    std::string encoded_signature;
    // std::string signature_hash;
    // std::string encoded_signature_hash;

    // Public key
    std::string raw_public_key;
    std::string encoded_public_key;
    std::string raw_public_key_hash;
    std::string encoded_public_key_hash;

    // Private key
    std::string raw_private_key;
    std::string encoded_private_key;
    std::string raw_private_key_hash;
    std::string encoded_private_key_hash;

    public:
    // Constructors
    ECC();
    ECC(std::string public_key_path, std::string private_key_path);
    ~ECC();

    std::string encode(std::string input);
    std::string decode(std::string input);
    std::string hash(std::string input);

    std::string get_public_key_path();
    void set_public_key_path(std::string path);

    std::string get_private_key_path();
    void set_private_key_path(std::string path);

    void generate_keys();
    void read_keys();
    void write_keys();
    void init_key_operations();

    void encrypt();
    void decrypt();
    void sign();
    bool verify();

    // Plaintext
    std::string get_raw_plaintext();
    std::string get_encoded_plaintext();
    std::string get_raw_plaintext_hash();
    std::string get_encoded_plaintext_hash();
    void set_raw_plaintext(std::string raw_plaintext);
    void set_encoded_plaintext(std::string encoded_plaintext);
    void set_raw_plaintext_hash(std::string raw_plaintext_hash);
    void set_encoded_plaintext_hash(std::string encoded_plaintext_hash);

    // Ciphertext
    std::string get_raw_ciphertext();
    std::string get_encoded_ciphertext();
    std::string get_raw_ciphertext_hash();
    std::string get_encoded_ciphertext_hash();
    void set_raw_ciphertext(std::string raw_ciphertext);
    void set_encoded_ciphertext(std::string encoded_ciphertext);
    void set_raw_ciphertext_hash(std::string raw_ciphertext_hash);
    void set_encoded_ciphertext_hash(std::string encoded_ciphertext_hash);

    // Signature
    std::string get_raw_signature();
    std::string get_encoded_signature();
    // std::string get_signature_hash();
    // std::string get_encoded_signature_hash();
    void set_raw_signature(std::string raw_signature);
    void set_encoded_signature(std::string encoded_signature);
    // void set_signature_hash(std::string signature_hash);
    // void set_encoded_signature_hash(std::string encoded_signature_hash);

    // Public key
    std::string get_raw_public_key();
    std::string get_encoded_public_key();
    std::string get_raw_public_key_hash();
    std::string get_encoded_public_key_hash();
    void set_raw_public_key(std::string raw_public_key);
    void set_encoded_public_key(std::string encoded_public_key);
    void set_raw_public_key_hash(std::string raw_public_key_hash);
    void set_encoded_public_key_hash(std::string encoded_public_key_hash);

    // Private key
    std::string get_raw_private_key();
    std::string get_encoded_private_key();
    std::string get_raw_private_key_hash();
    std::string get_encoded_private_key_hash();
    void set_raw_private_key(std::string raw_private_key);
    void set_encoded_private_key(std::string encoded_private_key);
    void set_raw_private_key_hash(std::string raw_private_key_hash);
    void set_encoded_private_key_hash(std::string encoded_private_key_hash);
};

#endif