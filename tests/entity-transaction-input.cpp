#include <iostream>

#include "crypto/ECC.cpp"
#include "entity/TransactionInput.cpp"

int main()
{
    ECC * ecc = new ECC();
    ecc->generate_keys();

    std::string ref_block_ID = ecc->encode(ecc->hash("123"));
    std::string ref_transaction_ID = ecc->encode(ecc->hash("456"));

    TransactionInput ti = TransactionInput();
    ti.set_ref_block_ID(ref_block_ID);
    ti.set_ref_transaction_ID(ref_transaction_ID);
    ti.set_ref_transaction_output_index(0);
    ti.set_index(0);
    ti.set_public_key_count(1);
    ti.add_public_key(ecc->get_encoded_public_key());
    ti.set_signature_count(1);
    ti.add_signature(
        ti.create_signature(ecc, 0)
    );
    // std::cout << ti.create_signature(ecc, 0) << std::endl;
    std::cout << ti.to_string() << std::endl;
}