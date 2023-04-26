#include "key.cpp"

int main()
{
    Key * rsa = new Key();
    rsa->generate_key_pair();
    rsa->write_public_key_file();
    rsa->write_private_key_file();

    unsigned char * message = (unsigned char *) "Hello World!";
    std::cout << message << std::endl;

    rsa->init_ciphertext();
    int encrypted_size = rsa->public_encrypt(message);
    std::cout << encrypted_size << rsa->ciphertext << std::endl;

    int decrypted_size = rsa->private_decrypt(encrypted_size);
    std::cout << decrypted_size << rsa->plaintext << std::endl;
}