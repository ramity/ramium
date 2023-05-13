#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#include <string>
#include <vector>

#include "crypto/ECC.cpp"
#include "entity/TransactionInput.cpp"
#include "entity/TransactionOutput.cpp"

class Transaction
{
    //! Constructors
    //* - Non-default constructor and deconstructor
    //*  + ECC instance pointer
    // [
    private:
        // Properties
        ECC * ecc;
    public:
        // Constructor
        Transaction(ECC * ecc);
        // Deconstructor
        ~Transaction();
    // ]

    //! ID
    //* - The double hash of the transaction data
    // [
    private:
        std::string ID;
    public:
        // Utility
        void calculate_ID();
        // Getters
        std::string get_ID();
        // Setters
        void set_ID(std::string ID);
    // ]

    //! Input count
    //* - The number of transactionInputs
    // [
    private:
        // Properties
        unsigned int input_count;
        std::string formatted_input_count;
    public:
        // Getters
        unsigned int get_input_count();
        std::string get_formatted_input_count();
        // Setters
        void set_input_count(unsigned int input_count);
        void set_formatted_input_count(std::string formatted_input_count);
    // ]

    //! Transaction inputs
    //* - Vector of transactionInput pointers
    // [
    private:
        // Properties
        std::vector<TransactionInput *> transaction_inputs;
    public:
        // Getters
        std::vector<TransactionInput *> get_transaction_inputs();
        // Setters
        void set_transaction_inputs(std::vector<TransactionInput *> transaction_inputs);
        // Add, remove, clear
        void add_transaction_input(TransactionInput * transaction_input);
        void remove_transaction_input(unsigned int index);
        void clear_transaction_inputs();
    // ]

    //! Output count
    //* - The number of transactionOutputs
    // [
    private:
        // Properties
        unsigned int output_count;
        std::string formatted_output_count;
    public:
        // Getters
        unsigned int get_output_count();
        std::string get_formatted_output_count();
        // Setters
        void set_output_count(unsigned int output_count);
        void set_formatted_output_count(std::string formatted_output_count);
    // ]

    //! Output transactions
    //* - Vector of transactionOutput pointers
    // [
    private:
        // Properties
        std::vector<TransactionOutput *> transaction_outputs;
    public:
        // Getters
        std::vector<TransactionOutput *> get_transaction_outputs();
        // Setters
        void set_transaction_outputs(std::vector<TransactionOutput *> transaction_outputs);
        // Add, remove, clear
        void add_transaction_output(TransactionOutput * transaction_output);
        void remove_transaction_output(unsigned int index);
        void clear_transaction_outputs();
    // ]

    //? Begin meta information

    //! Timestamp
    //* - When the transaction was created
    // [
    private:
        // Properties
        unsigned int timestamp;
        std::string formatted_timestamp;
    public:
        // Utility
        void set_timestamp_now();
        // Getters
        unsigned int get_timestamp();
        std::string get_formatted_timestamp();
        // Setters
        void set_timestamp(unsigned int timestamp);
        void set_formatted_timestamp(std::string formatted_timestamp);
    // ]

    //! Fees
    //* - Calculated fees (delta between input and output transactions)
    // [
    private:
        // Properties
        unsigned int fees;
        std::string formatted_fees;
    public:
        // Utility
        void calculate_fees();
        // Getters
        unsigned int get_fees();
        std::string get_formatted_fees();
        // Setters
        void set_fees(unsigned int fees);
        void set_formatted_fees(std::string formatted_fees);
    // ]

    //! Size
    //* - Size of transaction object (used in consideration of fees)
    // [
    private:
        // Properties
        unsigned int size;
        std::string formatted_size;
    public:
        // Utility
        void calculate_size();
        // Getters
        unsigned int get_size();
        std::string get_formatted_size();
        // Setters
        void set_size(unsigned int size);
        void set_formatted_size(std::string formatted_size);
    // ]
};

#endif