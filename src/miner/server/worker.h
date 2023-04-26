#ifndef __Worker_h__
#define __Worker_h__

#include "multithreading/Thread.h"
#include "multithreading/Queue.h"
#include "tcp/Stream.h"

class Worker : public Thread
{
    Queue<Stream *> &queue;

    public:
    Worker(Queue<Stream *> &queue);
    void * run();
};

#endif