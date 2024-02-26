
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void *high_prio_func(void *arg)
{
    pthread_attr_t tattr;
    pthread_t tid;
    int rv;
    struct sched_param param;

    /* initialized with default attributes */
    rv = pthread_attr_init(&tattr);
    assert(rv == 0);

    rv = pthread_attr_setschedpolicy(&tattr, SCHED_FIFO);
    assert(rv == 0);

    /* safe to get existing scheduling param */
    rv = pthread_attr_getschedparam(&tattr, &param);
    assert(rv == 0);

    rv = pthread_attr_setinheritsched(&tattr, PTHREAD_EXPLICIT_SCHED);
    assert(rv == 0);

    /* set the priority; others are unchanged */
    /* setting the new scheduling param */
    param.sched_priority = 80;
    rv = pthread_attr_setschedparam(&tattr, &param);
    assert(rv == 0);

    while (true)
    {
        // printf("blah \n");
        // usleep(1000*1000);
    }
}

int main(void)
{
    int rv;
    pthread_attr_t tattr;
    pthread_t tid;

    rv = pthread_attr_init(&tattr);
    assert(rv == 0);

    /* with new priority specified */
    rv = pthread_create(&tid, &tattr, high_prio_func, 0);
    assert(rv == 0);

    while (true)
        usleep(100);
}