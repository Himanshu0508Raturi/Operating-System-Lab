#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define N 5 // number of philosophers and chopsticks

sem_t chopstick[N]; // one semaphore per chopstick

void *philosopher(void *num)
{
    int id = *(int *)num;

    while (1)
    {
        // Thinking phase
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 3 + 1); // random think time

        int left = id;
        int right = (id + 1) % N;

        // Try to pick up left chopstick
        if (sem_trywait(&chopstick[left]) == 0)
        {
            // Try to pick up right chopstick
            if (sem_trywait(&chopstick[right]) == 0)
            {
                printf("Philosopher %d is eating using chopsticks %d and %d\n", id, left, right);
                sleep(rand() % 2 + 1); // eating time

                // Release both chopsticks
                sem_post(&chopstick[left]);
                sem_post(&chopstick[right]);
                printf("Philosopher %d has released chopsticks %d and %d\n", id, left, right);
            }
            else
            {
                // Couldn't get right chopstick, release left one
                sem_post(&chopstick[left]);
                printf("Philosopher %d released chopstick %d since right chopstick %d is unavailable\n",
                       id, left, right);
            }
        }
        else
        {
            printf("Philosopher %d couldn't pick left chopstick %d, will try again\n", id, left);
        }

        usleep(200); // small delay to reduce CPU usage
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t tid[N];
    int ids[N];

    srand(time(NULL)); // randomize sleep durations

    // Initialize semaphores (1 means available)
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    // Create philosopher threads
    for (int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &ids[i]);
    }

    // Wait (threads run infinitely)
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
