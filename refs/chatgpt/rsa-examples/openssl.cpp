#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#include "base64.cpp"

using namespace std;

int main() {
    // Generate a private/public key pair
    RSA * rsa = RSA_new();
    BIGNUM * bne = BN_new();

    BN_set_word(bne, 65537);
    RSA_generate_key_ex(rsa, 2048, bne, NULL);
    // EVP_PKEY* privateKey = EVP_PKEY_new();
    // EVP_PKEY_set1_RSA(privateKey, rsa);
    // RSA_free(rsa);

    // RSA* pubRsa = EVP_PKEY_get1_RSA(privateKey);
    // EVP_PKEY* publicKey = EVP_PKEY_new();
    // EVP_PKEY_set1_RSA(publicKey, pubRsa);
    // RSA_free(pubRsa);

    // Encrypt a message using the public key
    std::string message = "Hello, world!";
    unsigned char encrypted[RSA_size(rsa)];
    int encryptedLength = RSA_public_encrypt(message.size(), (const unsigned char*)message.c_str(), encrypted, rsa, RSA_PKCS1_OAEP_PADDING);

    // Decrypt the message using the private key
    unsigned char decrypted[encryptedLength];
    int decryptedLength = RSA_private_decrypt(encryptedLength, encrypted, decrypted, rsa, RSA_PKCS1_OAEP_PADDING);

    // Sign a message using the private key
    unsigned char signature[RSA_size(rsa)];
    unsigned int signatureLength;
    RSA_sign(NID_sha256, decrypted, decryptedLength, signature, &signatureLength, rsa);

    // Verify the signature using the public key
    int result = RSA_verify(NID_sha256, decrypted, decryptedLength, signature, signatureLength, rsa);

    std::cout << "Original message: " << message << std::endl;
    std::cout << "Encrypted message: " << base64_encode(reinterpret_cast<const unsigned char*>(encrypted), encryptedLength) << std::endl;
    std::cout << "Decrypted message: " << std::string(reinterpret_cast<const char*>(decrypted), decryptedLength) << std::endl;
    std::cout << "Signature: " << base64_encode(reinterpret_cast<const unsigned char*>(signature), signatureLength) << std::endl;
    std::cout << "Signature verified: " << std::boolalpha << (result == 1) << std::endl;

    return 0;
}