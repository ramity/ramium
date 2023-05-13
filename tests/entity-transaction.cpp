#include <iostream>
#include <string>
#include <chrono>

#include "crypto/ECC.cpp"
#include "entity/Transaction.cpp"
#include "entity/TransactionInput.cpp"
#include "entity/TransactionOutput.cpp"

int main()
{
    ECC * ecc = new ECC();
    ecc->generate_keys();

    TransactionInput * ti = new TransactionInput();
    ti->set_ref_block_ID(ecc->hash("123"));
    ti->set_ref_transaction_ID(ecc->hash("456"));
    ti->set_ref_transaction_output_index(0);
    ti->set_index(0);
    ti->set_public_key_count(1);
    ti->add_public_key(ecc->get_encoded_public_key());
    ti->set_signature_count(1);
    ti->add_signature(
        ti->create_signature(ecc, 0)
    );

    TransactionOutput * to = new TransactionOutput();
    to->set_index(0);
    to->set_amount(100000);
    to->set_public_key_hash_count(1);
    to->add_public_key_hash(
        ecc->get_encoded_public_key_hash()
    );
    to->set_spent(false);

    Transaction * t = new Transaction(ecc);
    t->set_input_count(1);
    t->add_transaction_input(ti);
    t->set_output_count(1);
    t->add_transaction_output(to);
    t->calculate_ID();
    t->set_timestamp(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    t->set_fees(420);
    t->set_size(0);

    delete ti;
    delete to;
    delete t;

    return 0;
}