#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // buffer size

int buf[N];
int in = 0, out = 0;

sem_t empty;         // how many empty slots
sem_t full;          // how many filled slots
pthread_mutex_t mtx; // protects buf, in, out

void *producer(void *arg)
{
    int i = 0;
    while (1)
    {
        sem_wait(&empty);         // wait for an empty slot
        pthread_mutex_lock(&mtx); // lock buffer

        buf[in] = i;
        printf("Producer produces -> %d\n", i);
        in = (in + 1) % N;
        i++;

        pthread_mutex_unlock(&mtx);
        sem_post(&full); // one more full slot

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while (1)
    {
        sem_wait(&full);          // wait for an item
        pthread_mutex_lock(&mtx); // lock buffer

        int item = buf[out];
        printf("Consumer consumes <- %d\n", item);
        out = (out + 1) % N;

        pthread_mutex_unlock(&mtx);
        sem_post(&empty); // one more empty slot

        sleep(2);
    }
    return NULL;
}

int main(void)
{
    pthread_t prod, cons;

    sem_init(&empty, 0, N); // N empty slots at start
    sem_init(&full, 0, 0);  // 0 full slots at start
    pthread_mutex_init(&mtx, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // sem_destroy(&empty);
    // sem_destroy(&full);
    // pthread_mutex_destroy(&mtx);

    return 0;
}
