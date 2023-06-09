#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include <string>
#include <netinet/in.h>
#include "stream.h"

class Acceptor
{
    int m_lsd;
    int m_port;
    std::string m_address;
    bool m_listening;

    public:
    Acceptor(int port, const char * address = "");
    ~Acceptor();
    int start();
    Stream * accept();

    private:
    Acceptor() {};
};

#endif