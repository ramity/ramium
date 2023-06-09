#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

class Thread
{
    public:
    Thread();
    virtual ~Thread();
    int start();
    int join();
    int detach();
    pthread_t self();
    virtual void * run() = 0;

    private:
    pthread_t m_tid;
    int m_running;
    int m_detached;
};

#endif