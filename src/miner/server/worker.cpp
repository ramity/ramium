#include "worker.h"

#include <cstring>

#include "multithreading/queue.h"
#include "tcp/stream.h"


// Explicitly include due to templating
// #include "multithreading/queue.cpp"

// Known datatype sizes
int int_bytes_per_element = 4;
int float_bytes_per_element = 4;
int double_bytes_per_element = 8;

Worker::Worker(Queue<Stream *> &queue) : queue(queue){}

void * Worker::run()
{
    int incoming_buffer_size = 1000000000;
    int outgoing_buffer_size = 1000000000;
    char * incoming_buffer = new char[incoming_buffer_size];
    char * outgoing_buffer = new char[outgoing_buffer_size];

    for (int i = 0;; i++)
    {
        // Pause thread and wait for a Stream to get added to queue
        printf("thread %lu, loop %d - waiting for item...\n", (long unsigned int) self(), i);
        Stream * stream = this->queue.remove();
        printf("thread %lu, loop %d - got one item\n", (long unsigned int) self(), i);

        while (1)
        {
            // Intake request
            stream->receive_message(incoming_buffer);

            // Extract control values
            int incoming_bytes;
            int incoming_command;
            memcpy(&incoming_bytes, &incoming_buffer[0], int_bytes_per_element);
            memcpy(&incoming_command, &incoming_buffer[4], int_bytes_per_element);

            // Exit command
            if (incoming_command == 0)
            {
                printf("thread %lu, recieved exit command\n", (long unsigned int) self());
                break;
            }

            // Echo command
            else if (incoming_command == 1)
            {
                printf("thread %lu, recieved echo command\n", (long unsigned int) self());
                stream->send_message(incoming_buffer, incoming_bytes);
                printf("thread %lu, echoed back to the client\n", (long unsigned int) self());
            }
        }

        delete stream;
    }

    delete incoming_buffer;
    delete outgoing_buffer;

    return NULL;
}