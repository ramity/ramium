#ifndef __Queue_h__
#define __Queue_h__

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