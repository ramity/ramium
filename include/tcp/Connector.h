#ifndef __connector_h__
#define __connector_h__

#include <netinet/in.h>
#include "stream.h"

class Connector
{
    public:
    Stream * connect(const char * server, int port);
    Stream * connect(const char * server, int port, int timeout);

    private:
    int resolveHostName(const char * host, struct in_addr * addr);
};

#endif