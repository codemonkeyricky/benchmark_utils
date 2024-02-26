#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define THREAD_1_PRIORITY 50
#define THREAD_2_PRIORITY 60

void *thread1_function(void *arg)
{
    int thread_number = *(int *)arg;
    struct sched_param params;

    // Set the thread priority
    params.sched_priority = THREAD_1_PRIORITY;

    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &params) != 0)
    {
        perror("pthread_setschedparam");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to simulate a thread doing some work
    while (1)
    {
        // printf("Thread %d is running\n", thread_number);
        // sleep(1);
    }

    pthread_exit(NULL);
}

void *thread_other_function(void *arg)
{
    int thread_number = *(int *)arg;
    struct sched_param params;

    // Set the thread priority
    params.sched_priority = THREAD_2_PRIORITY;

    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &params) != 0)
    {
        perror("pthread_setschedparam");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to simulate a thread doing some work
    while (1)
    {
        // printf("Thread %d is running\n", thread_number);
        // sleep(1);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int result_code, i;

    // Create two threads
    for (i = 0; i < NUM_THREADS; i++)
    {
        thread_args[i] = i;
        if (i == 0)
            result_code = pthread_create(&threads[i], NULL, thread1_function, &thread_args[i]);
        else 
            result_code = pthread_create(&threads[i], NULL, thread_other_function, &thread_args[i]);
        if (result_code != 0)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    for (i = 0; i < NUM_THREADS; i++)
    {
        result_code = pthread_join(threads[i], NULL);
        if (result_code != 0)
        {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
