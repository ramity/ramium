#include <iostream>
#include <string>
#include <botan/auto_rng.h>
#include <botan/pubkey.h>
#include <botan/rsa.h>
#include <botan/base64.h>

using namespace Botan;

int main() {
    // Generate a private/public key pair
    AutoSeeded_RNG rng;
    RSA_PrivateKey privateKey(rng, 2048);
    RSA_PublicKey publicKey = privateKey;

    // Encrypt a message using the public key
    std::string message = "Hello, world!";
    std::string encrypted = publicKey.encrypt(message, rng);

    // Decrypt the message using the private key
    std::string decrypted = privateKey.decrypt(encrypted);

    // Sign a message using the private key
    PK_Signer signer(privateKey, "EMSA4(SHA-256)");
    signer.update(decrypted);
    std::vector<uint8_t> signature = signer.signature(rng);

    // Verify the signature using the public key
    PK_Verifier verifier(publicKey, "EMSA4(SHA-256)");
    verifier.update(decrypted);
    bool result = verifier.check_signature(signature);

    std::cout << "Original message: " << message << std::endl;
    std::cout << "Encrypted message: " << base64_encode(reinterpret_cast<const unsigned char*>(encrypted.data()), encrypted.size()) << std::endl;
    std::cout << "Decrypted message: " << decrypted << std::endl;
    std::cout << "Signature: " << base64_encode(reinterpret_cast<const unsigned char*>(signature.data()), signature.size()) << std::endl;
    std::cout << "Signature verified: " << std::boolalpha << result << std::endl;

    return 0;
}