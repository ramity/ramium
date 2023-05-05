#include <iostream>
#include <string>

#include "crypto/ECC.cpp"

int main()
{
    // Config
    std::string message = "Hello, world!";

    // Init
    ECC ecc = ECC();
    ecc.generate_keys();
    ecc.set_raw_plaintext(message);

    // Make sure decryptoed output == message
    ecc.encrypt();
    ecc.decrypt();
    if (ecc.get_raw_plaintext() != message)
    {
        std::cout << "[-] Failed ecc decryption" << std::endl;
        return 1;
    }

    // Sign and verify the plaintext message hash
    ecc.sign();
    if (!ecc.verify())
    {
        std::cout << "[-] Failed verification" << std::endl;
        return 1;
    }

    // Write keys, create new ECC instance, read keys, transfer raw ciphertext, decrypt, check if raw_plaintexts match 
    ecc.write_keys();
    ECC ecc2 = ECC();
    ecc2.read_keys();
    ecc2.set_raw_ciphertext(ecc.get_raw_ciphertext());
    ecc2.decrypt();
    if (ecc.get_raw_plaintext() != ecc2.get_raw_plaintext())
    {
        std::cout << "[-] Failed write, read, decrypt, compare test" << std::endl;
        return 1;
    }

    std::cout << ecc.get_encoded_signature() << std::endl;
    // std::cout << ecc2.get_encoded_public_key_hash() << std::endl;

    return 0;
}