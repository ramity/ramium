#ifndef __STREAM_H__
#define __STREAM_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>


class Stream
{
    int socket_descriptor;
    std::string peer_address;
    int peer_port;

    public:

    friend class Acceptor;
    friend class Connector;
    ~Stream();
    ssize_t send(const char * buffer, size_t len);
    ssize_t receive(char * buffer, size_t len, int timeout = 0);
    bool send_message(char * buffer, int message_bytes);
    bool receive_message(char * buffer);
    bool close_message();
    std::string getPeerIP();
    int getPeerPort();
    enum
    {
        connectionClosed = 0,
        connectionReset = -1,
        connectionTimedOut = -2
    };

    private:

    bool waitForReadEvent(int timeout);
    Stream(int sd, struct sockaddr_in * address);
    Stream();
    Stream(const Stream &stream);
};

#endif