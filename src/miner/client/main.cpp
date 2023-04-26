#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <iostream>
#include <random>
#include <cstring>
#include <math.h>

#include "tcp/connector.cpp"
#include "tcp/stream.cpp"

// Known datatype sizes
int int_bytes_per_element = 4;
int float_bytes_per_element = 4;
int double_bytes_per_element = 8;

// command: 0   exit
// command: 1   echo

int main()
{
    // Echos incoming message back to the client

    // Echo command incoming buffer format:
    // message_bytes        int(1)
    // command              int(1)


    // Init vars for debug stats
    std::chrono::steady_clock clock;
    std::chrono::steady_clock::time_point outgoing_start;
    std::chrono::steady_clock::time_point outgoing_stop;
    std::chrono::steady_clock::time_point incoming_start;
    std::chrono::steady_clock::time_point incoming_stop;


    // Connection config vars
    std::string ip_string = "miner_server";
    const char * ip = ip_string.c_str();
    int port = 65535;

    // Buffer vars
    int outgoing_buffer_size = 1000000000;
    int incoming_buffer_size = 1000000000;
    char * outgoing_buffer = new char[outgoing_buffer_size];
    char * incoming_buffer = new char[incoming_buffer_size];

    // TCP setup
    Connector * connector = new Connector();
    Stream * stream = connector->connect(ip, port);
    if (stream == NULL)
    {
        printf("Failed to connect to %s:%i\n", ip, port);
        return 1;
    }

    // Echo message
    int outgoing_command = 1;
    int outgoing_text_size = 5000000;
    for (int z = (2 * int_bytes_per_element); z < (2 * int_bytes_per_element) + outgoing_text_size; z++)
        outgoing_buffer[z] = '0';
    int outgoing_message_bytes = (2 * int_bytes_per_element) + outgoing_text_size;
    memcpy(&outgoing_buffer[0], &outgoing_message_bytes, int_bytes_per_element);
    memcpy(&outgoing_buffer[4], &outgoing_command, int_bytes_per_element);

    // Send
    outgoing_start = clock.now();
    stream->send_message(outgoing_buffer, outgoing_message_bytes);
    outgoing_stop = clock.now();

    // Receive
    incoming_start = clock.now();
    stream->receive_message(incoming_buffer);
    incoming_stop = clock.now();

    // Extract
    int incoming_message_bytes;
    memcpy(&incoming_message_bytes, &incoming_buffer[0], int_bytes_per_element);
    int incoming_message_command;
    memcpy(&incoming_message_command, &incoming_buffer[4], int_bytes_per_element);

    // Compare
    bool match = true;
    for (int z = 0; z < outgoing_message_bytes; z++)
    {
        if (outgoing_buffer[z] != incoming_buffer[z])
        {
            match = false;
            break;
        }
    }

    if (match)
    {
        printf("PASS: Echo REASON: Texts match.\n");
    }
    else
    {
        printf("FAIL: Echo REASON: Text mismatch.\n");
    }

    // Output debug stats
    auto outgoing_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(outgoing_stop - outgoing_start);
    auto incoming_duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(incoming_stop - incoming_start);
    printf("outgoing_duration_ns: %lu ns\n", outgoing_duration_ns.count());
    printf("incoming_duration_ns: %lu ns\n", incoming_duration_ns.count());
    printf("outgoing rate: %f bytes/ns\n", 1.0 * outgoing_message_bytes / outgoing_duration_ns.count());
    printf("incoming rate: %f bytes/ns\n", 1.0 * incoming_message_bytes / incoming_duration_ns.count());

    stream->close_message();

    // Close stream by freeing memory
    delete stream;
    delete incoming_buffer;
    delete outgoing_buffer;

    return 1;
}