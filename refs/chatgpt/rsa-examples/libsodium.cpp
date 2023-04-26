#include <iostream>
#include <string>
#include <sodium.h>
#include <stdexcept>

using namespace std;

int main() {
    // Initialize the library
    if (sodium_init() < 0) {
        throw runtime_error("Failed to initialize libsodium");
    }

    // Generate a private/public key pair
    unsigned char privateKey[crypto_box_SECRETKEYBYTES];
    unsigned char publicKey[crypto_box_PUBLICKEYBYTES];
    crypto_box_keypair(publicKey, privateKey);

    // Encrypt a message using the public key
    std::string message = "Hello, world!";
    std::string nonce(crypto_box_NONCEBYTES, 0);
    std::string encrypted(crypto_box_MACBYTES + message.size(), 0);
    if (crypto_box_easy(reinterpret_cast<unsigned char*>(&encrypted[0]), reinterpret_cast<const unsigned char*>(message.c_str()), message.size(), reinterpret_cast<const unsigned char*>(&nonce[0]), publicKey, privateKey) != 0) {
        throw runtime_error("Failed to encrypt message");
    }

    // Decrypt the message using the private key
    std::string decrypted(message.size(), 0);
    if (crypto_box_open_easy(reinterpret_cast<unsigned char*>(&decrypted[0]), reinterpret_cast<const unsigned char*>(&encrypted[crypto_box_MACBYTES]), encrypted.size() - crypto_box_MACBYTES, reinterpret_cast<const unsigned char*>(&nonce[0]), publicKey, privateKey) != 0) {
        throw runtime_error("Failed to decrypt message");
    }

    // Sign a message using the private key
    unsigned char signature[crypto_sign_BYTES];
    unsigned long long signatureLength;
    if (crypto_sign_detached(signature, &signatureLength, reinterpret_cast<const unsigned char*>(decrypted.c_str()), decrypted.size(), privateKey) != 0) {
        throw runtime_error("Failed to sign message");
    }

    // Verify the signature using the public key
    if (crypto_sign_verify_detached(signature, reinterpret_cast<const unsigned char*>(decrypted.c_str()), decrypted.size(), publicKey) != 0) {
        throw runtime_error("Signature verification failed");
    }

    std::cout << "Original message: " << message << std::endl;
    std::cout << "Encrypted message: " << sodium_bin2base64(reinterpret_cast<unsigned char*>(&encrypted[0]), encrypted.size(), sodium_base64_VARIANT_ORIGINAL_NO_PADDING) << std::endl;
    std::cout << "Decrypted message: " << decrypted << std::endl;
    std::cout << "Signature: " << sodium_bin2base64(signature, signatureLength, sodium_base64_VARIANT_ORIGINAL_NO_PADDING) << std::endl;
    std::cout << "Signature verified: true" << std::endl;

    return 0;
}