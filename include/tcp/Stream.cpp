#ifndef __STREAM_CPP__
#define __STREAM_CPP__

#include "stream.h"

#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

Stream::Stream(int sd, struct sockaddr_in * address) : socket_descriptor(sd)
{
    char ip[50];
    inet_ntop(PF_INET, (struct in_addr *) &(address->sin_addr.s_addr), ip, sizeof(ip) - 1);
    this->peer_address = ip;
    this->peer_port = ntohs(address->sin_port);
}

Stream::~Stream()
{
    close(this->socket_descriptor);
}

ssize_t Stream::send(const char * buffer, size_t len)
{
    return write(this->socket_descriptor, buffer, len);
}

ssize_t Stream::receive(char * buffer, size_t len, int timeout)
{
    if (timeout <= 0)
    {
        return read(this->socket_descriptor, buffer, len);
    }

    if (waitForReadEvent(timeout) == true)
    {
        return read(this->socket_descriptor, buffer, len);
    }

    return connectionTimedOut;
}

bool Stream::send_message(char * buffer, int message_bytes)
{
    int stream_bytes;
    int pending_bytes = message_bytes;

    while(pending_bytes > 0)
    {
        stream_bytes = this->send(&buffer[message_bytes - pending_bytes], pending_bytes);

        if (stream_bytes < 0)
        {
            printf("ERROR: send_message failed\n");
            printf("outgoing: %i of %i bytes\n", message_bytes - pending_bytes, message_bytes);
            printf("The last error message is: %s\n", strerror(errno));
            return false;
        }

        pending_bytes -= stream_bytes;
        printf("outgoing: %i of %i bytes\n", message_bytes - pending_bytes, message_bytes);
    }

    return true;
}

bool Stream::receive_message(char * buffer)
{
    // Get message size from first four bytes
    int message_bytes;
    this->receive(&buffer[0], 4);
    memcpy(&message_bytes, &buffer[0], 4); 

    int stream_bytes;
    int pending_bytes = message_bytes - 4;

    while (pending_bytes > 0)
    {
        stream_bytes = this->receive(&buffer[message_bytes - pending_bytes], pending_bytes);

        if (stream_bytes < 0)
        {
            printf("ERROR: receive_message failed\n");
            printf("incoming: %i of %i bytes\n", message_bytes - pending_bytes, message_bytes);
            printf("The last error message is: %s\n", strerror(errno));
            return false;
        }

        pending_bytes -= stream_bytes;
        // printf("incoming: %i of %i bytes\n", message_bytes - pending_bytes, message_bytes);
    }

    return true;
}

bool Stream::close_message()
{
    int message_bytes = 8;
    int message_command = 0;
    char * message_buffer = new char[8];
    memcpy(&message_buffer[0], &message_bytes, 4);
    memcpy(&message_buffer[4], &message_command, 4);

    int stream_bytes = this->send(&message_buffer[0], message_bytes);

    if (stream_bytes < 0)
    {
        printf("ERROR: close_message failed\n");
        printf("The last error message is: %s\n", strerror(errno));
        return false;
    }

    return true;
}

std::string Stream::getPeerIP()
{
    return this->peer_address;
}

int Stream::getPeerPort()
{
    return this->peer_port;
}

bool Stream::waitForReadEvent(int timeout)
{
    fd_set sdset;
    struct timeval tv;

    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    FD_ZERO(&sdset);
    FD_SET(this->socket_descriptor, &sdset);

    if (select(this->socket_descriptor + 1, &sdset, NULL, NULL, &tv) > 0)
    {
        return true;
    }

    return false;
}

#endif