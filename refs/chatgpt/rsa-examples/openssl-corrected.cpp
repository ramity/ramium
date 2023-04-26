#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#include "base64.cpp"

int main()
{
    // Config
    int key_length = 4096;
    int public_exponent = 65537;
    int modulus_size = key_length / 8;

    // Generate a private/public key pair
    RSA * rsa = RSA_new();
    BIGNUM * bne = BN_new();
    BN_set_word(bne, public_exponent);
    RSA_generate_key_ex(rsa, key_length, bne, NULL);

    // Encrypt a message using the public key
    std::string message = "Hello, world!";
    unsigned char encrypted[modulus_size];
    int encryptedLength = RSA_public_encrypt(message.size(), reinterpret_cast<const unsigned char*>(message.c_str()), encrypted, rsa, RSA_PKCS1_OAEP_PADDING);

    // Decrypt the message using the private key
    unsigned char decrypted[modulus_size];
    int decryptedLength = RSA_private_decrypt(encryptedLength, encrypted, decrypted, rsa, RSA_PKCS1_OAEP_PADDING);

    // Sign a message using the private key
    unsigned char signature[modulus_size];
    unsigned int signatureLength;
    RSA_sign(NID_sha256, decrypted, decryptedLength, signature, &signatureLength, rsa);

    // Verify the signature using the public key
    // int result = RSA_verify(NID_sha256, decrypted, decryptedLength, signature, signatureLength, rsa);
    int result = RSA_verify(NID_sha256, reinterpret_cast<const unsigned char*>(message.c_str()), message.size(), signature, signatureLength, rsa);

    std::cout << "Original message: " << message << std::endl;
    std::cout << "Encrypted message: " << base64_encode(reinterpret_cast<const unsigned char*>(encrypted), encryptedLength) << std::endl;
    std::cout << "Decrypted message: " << std::string(reinterpret_cast<const char*>(decrypted), decryptedLength) << std::endl;
    std::cout << "Signature: " << base64_encode(reinterpret_cast<const unsigned char*>(signature), signatureLength) << std::endl;
    std::cout << "Signature verified: " << std::boolalpha << (result == 1) << std::endl;

    return 0;
}