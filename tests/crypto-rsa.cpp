#include "crypto/RSACipher.cpp"

int main()
{
    // Config
    int key_length = 4096;
    int public_exponent = 65537;
    std::string message = "Hello, world!";

    // Check if plaintext does not match message
    RSACipher rsa = RSACipher(key_length, public_exponent);
    rsa.generate_keys();
    rsa.set_plaintext(message);
    rsa.encrypt();
    rsa.decrypt();
    if (rsa.get_plaintext() != message)
    {
        std::cout << "[-] Failed rsa decryption" << std::endl;
        return 1;
    }

    // Check if verification fails
    rsa.sign();
    if (rsa.verify() == 0)
    {
        std::cout << "[-] Failed rsa verification" << std::endl;
        return 1;
    }

    // Check if plaintext does not match message
    RSACipher rsa_2 = RSACipher(key_length, public_exponent);
    rsa_2.read_keys();
    rsa_2.set_plaintext(message);
    rsa_2.encrypt();
    rsa_2.decrypt();
    if (rsa_2.get_plaintext() != message)
    {
        std::cout << "[-] Failed rsa_2 decryption" << std::endl;
        return 1;
    }

    // Check if verification fails
    rsa_2.sign();
    if (rsa_2.verify() == 0)
    {
        std::cout << "[-] Failed rsa_2 verification" << std::endl;
        return 1;
    }

    // std::cout << rsa.get_plaintext() << std::endl;
    // std::cout << rsa.get_ciphertext() << std::endl;
    // std::cout << rsa.get_signature() << std::endl;
    // std::cout << std::boolalpha << (result == 1) << std::endl;

    return 0;
}