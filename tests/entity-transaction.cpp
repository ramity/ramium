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

    std::string ref_block_ID = ecc->encode(ecc->hash("123"));
    std::string ref_transaction_ID = ecc->encode(ecc->hash("456"));

    TransactionInput * ti = new TransactionInput();
    ti->set_ref_block_ID(ref_block_ID);
    ti->set_ref_transaction_ID(ref_transaction_ID);
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

    Transaction * t = new Transaction();
    t->set_input_count(1);
    t->add_transaction_input(ti);
    t->set_output_count(1);
    t->add_transaction_output(to);
    t->set_ID(t->to_hash(ecc));
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::seconds unix_time = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    std::time_t unix_timestamp = unix_time.count();
    unsigned int timestamp = static_cast<unsigned int>(unix_timestamp);
    t->set_timestamp(timestamp);
    t->set_fees(420);
    t->set_size(0);
    t->set_block_height(100);
    t->set_confirmations(10);
    std::string output = t->to_string();
    unsigned int size = output.size();
    t->set_size(size);

    std::cout << t->to_string() << std::endl;

    delete ti;
    delete to;
    delete t;

    return 0;
}