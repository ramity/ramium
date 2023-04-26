#include <iostream>
#include <string>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>

using namespace CryptoPP;

int main() {
    // Generate a private/public key pair
    AutoSeededRandomPool rng;
    InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 2048);
    RSA::PrivateKey privateKey(params);
    RSA::PublicKey publicKey(params);

    // Encrypt a message using the public key
    std::string message = "Hello, world!";
    std::string encrypted;
    RSAES_OAEP_SHA_Encryptor encryptor(publicKey);
    StringSource(message, true, new PK_EncryptorFilter(rng, encryptor, new StringSink(encrypted)));

    // Decrypt the message using the private key
    std::string decrypted;
    RSAES_OAEP_SHA_Decryptor decryptor(privateKey);
    StringSource(encrypted, true, new PK_DecryptorFilter(rng, decryptor, new StringSink(decrypted)));

    // Sign a message using the private key
    std::string signature;
    RSASSA_PKCS1v15_SHA_Signer signer(privateKey);
    StringSource(decrypted, true, new SignerFilter(rng, signer, new StringSink(signature)));

    // Verify the signature using the public key
    RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);
    bool result = false;
    StringSource(decrypted + signature, true, new SignatureVerificationFilter(verifier, new ArraySink((byte*)&result, sizeof(result))));

    std::cout << "Original message: " << message << std::endl;
    std::cout << "Encrypted message: " << base64_encode(reinterpret_cast<const unsigned char*>(encrypted.data()), encrypted.size()) << std::endl;
    std::cout << "Decrypted message: " << decrypted << std::endl;
    std::cout << "Signature: " << base64_encode(reinterpret_cast<const unsigned char*>(signature.data()), signature.size()) << std::endl;
    std::cout << "Signature verified: " << std::boolalpha << result << std::endl;

    return 0;
}