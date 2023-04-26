#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <math.h>

#include "multithreading/thread.cpp"
#include "multithreading/queue.cpp"
#include "tcp/acceptor.cpp"
#include "tcp/stream.cpp"
#include "worker.cpp"

int main()
{
    // Workers
    int workers = 64;
    int port = 65535;
    const char * ip = std::string("0.0.0.0").c_str();
    Queue<Stream *> queue;

    for (int i = 0; i < workers; i++)
    {
        Worker * thread = new Worker(queue);

        if (!thread)
        {
            printf("Could not create MinerThread %d\n", i);
            exit(1);
        }

        thread->start();
    }

    // Create an acceptor then start listening for connections
    Acceptor * connectionAcceptor = new Acceptor(port, ip);

    if (!connectionAcceptor || connectionAcceptor->start() != 0)
    {
        printf("Could not create an connection acceptor\n");
        exit(1);
    }

    // Add a work item to the queue for each connection
    while (1)
    {
        Stream * connection = connectionAcceptor->accept();

        if (!connection)
        {
            printf("Could not accept a connection\n");
            continue;
        }

        queue.add(connection);
    }

    exit(0);
}