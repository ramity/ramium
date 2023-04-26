#include "Queue.h"

template <typename T>
Queue<T>::Queue()
{
    pthread_mutex_init(&this->mutex, NULL);
    pthread_cond_init(&this->cond, NULL);
}

template <typename T>
Queue<T>::~Queue()
{
    pthread_mutex_destroy(&this->mutex);
    pthread_cond_destroy(&this->cond);
}

template <typename T>
void Queue<T>::add(T item)
{
    pthread_mutex_lock(&this->mutex);
    this->queue.push_back(item);
    pthread_cond_signal(&this->cond);
    pthread_mutex_unlock(&this->mutex);
}

template <typename T>
T Queue<T>::remove()
{
    pthread_mutex_lock(&this->mutex);

    while (this->queue.size() == 0)
    {
        pthread_cond_wait(&this->cond, &this->mutex);
    }

    T item = this->queue.front();
    this->queue.pop_front();
    pthread_mutex_unlock(&this->mutex);

    return item;
}

template <typename T>
int Queue<T>::size()
{
    pthread_mutex_lock(&this->mutex);
    int size = this->queue.size();
    pthread_mutex_unlock(&this->mutex);

    return size;
}