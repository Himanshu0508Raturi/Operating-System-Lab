#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // philosophers = chopsticks

sem_t chopstick[N];

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    // Order to avoid deadlock: always take lower id first
    int first = left < right ? left : right;
    int second = left < right ? right : left;

    while (1)
    {
        // think
        printf("Philo %d is thinking\n", id);
        sleep(1);

        // take chopsticks
        sem_wait(&chopstick[first]);
        sem_wait(&chopstick[second]);

        // eat
        printf("Philo %d is eating with %d & %d\n", id, left, right);
        sleep(1);

        // put down chopsticks
        sem_post(&chopstick[second]);
        sem_post(&chopstick[first]);

        printf("Philo %d finished eating\n", id);
    }

    return NULL;
}

int main(void)
{
    pthread_t tid[N];
    int id[N];

    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
