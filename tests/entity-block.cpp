#include <iostream>
#include <string>
#include <cryptopp/base64.h>

#include "crypto/ECC.cpp"
#include "entity/Block.cpp"
#include "entity/Transaction.cpp"
#include "entity/TransactionInput.cpp"
#include "entity/TransactionOutput.cpp"

int main()
{
    ECC * ecc = new ECC();
    ecc->generate_keys();

    Block * b = new Block(ecc);
    b->set_previous_block_hash(ecc->hash(ecc->hash("prev")));
    b->set_timestamp_now();
    b->set_difficulty_target("\x80\x80" + std::string(62, '\x7F'));
    b->set_nonce(0);

    b->set_next_block_hash(ecc->hash(ecc->hash("next")));
    b->set_height(0);
    b->set_confirmations(0);

    b->set_transaction_count(6);
    for (unsigned int z = 0; z < b->get_transaction_count(); z++)
    {
        TransactionInput * ti = new TransactionInput();
        ti->set_ref_block_ID(ecc->encode(ecc->hash("123")));
        ti->set_ref_transaction_ID(ecc->encode(ecc->hash("456")));
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
        t->calculate_ID(ecc);
        t->set_timestamp_now();
        t->set_fees(420);
        t->set_size(0);
        t->set_block_height(100);
        t->set_confirmations(10);
        std::string output = t->to_string();
        unsigned int size = output.size();
        t->set_size(size);

        b->add_transaction(t);
    }

    b->build_transaction_IDs();
    b->build_merkle_tree();
    // b->print_merkle_tree();

    unsigned int hash_rate = 900000;
    unsigned int desired_seconds = 5;
    unsigned int desired_hashes = hash_rate * desired_seconds;
    unsigned int max_value = 4294967295;
    unsigned int difficulty_value = max_value - desired_hashes;
    std::cout << difficulty_value << std::endl;

    b->calculate_preamble();

    for (unsigned int z = 0; z < 10000000; z++)
    {
        std::cout << "\r" << z;
        if (b->proof_of_work())
        {
            std::cout << std::endl;
            std::cout << "pog!" << std::endl;
            std::cout << ecc->encode(b->get_ID()) << std::endl;
            std::cout << ecc->encode(b->get_difficulty_target()) << std::endl;
            std::cout << b->get_formatted_nonce() << std::endl;
            break;
        }
    }

    std::cout << std::endl;

    return 0;
}