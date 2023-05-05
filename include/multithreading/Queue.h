#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <pthread.h>
#include <list>

template <typename T>
class Queue
{
    std::list<T> queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

    public:
    Queue();
    ~Queue();
    void add(T item);
    T remove();
    int size();
};

#endif