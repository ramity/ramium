#include <iostream>

#include "crypto/ECC.cpp"
#include "entity/TransactionOutput.cpp"

int main()
{
    ECC * ecc = new ECC();
    ecc->generate_keys();

    TransactionOutput to = TransactionOutput();
    to.set_index(0);
    to.set_amount(100);
    to.set_public_key_hash_count(1);
    to.add_public_key_hash(
        ecc->get_encoded_public_key_hash()
    );
    to.set_spent(false);

    std::cout << to.to_string() << std::endl;

    return 0;
}